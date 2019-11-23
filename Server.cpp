/*
 * A simple TCP select server that accepts multiple connections and echo message back to the clients
 * For use in CPSC 441 lectures
 * Instructor: Prof. Mea Wang
 */

#include "Server.h"
#include "DatabaseManager.h"
#include "ChatManager.h"
#include "User.h"
#include<algorithm>
#include <iostream>

#include <sys/socket.h>

#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()


using namespace std;

const int BUFFERSIZE = 1024;		// Size the message buffers
const int MAXPENDING = 10;		// Maximum pending connections
const int MAXCLIENTS = 20;		// Maximum capacity of clients on the server at the same time

fd_set recvSockSet;			// The set of descriptors for incoming connections
int maxDesc = 0;			// The max descriptor
bool terminated = false;    

//global variables
string header;
string commandSent;
string requestId;
string timeStamp;

int  initServer(int&, int port);
void processSockets(fd_set);
void sendData(int, char[], int);
void receiveData(int, char[], int&);
void handleRequest(int sock, string request);
void serverHeader(string request);
void getTimeStamp();

DatabaseManager dbMan;
ChatManager chatMan;

int main(int argc, char *argv[])
{
    int serverSock;						// server socket descriptor
    int clientSock;						// client socket descriptor
	int clientSocket[MAXCLIENTS];		// capacity of clients on server at a time
    struct sockaddr_in clientAddr;		// address of the client
	int addrSize;
	int sockDesc;

    struct timeval timeout = {0, 10};  // The timeout value for select()
    struct timeval selectTime;

	char inBuffer[1024];

	fd_set tempRecvSockSet;            // Temp. receive socket set for select()

	// A temporary message
	char *message = "CPSC441 Network Server\n";

	int i;
	// Initialize all the client sockets
	for (i = 0; i < MAXCLIENTS; i++)
		clientSocket[i] = 0;

	std::string machineId(40,'0');
	std::string commandSent(3,'1');
	std::string requestId(20,'2');
	std::string userId(12,'3');
	std::string timeStamp(8,'4');
	//std::string *splitHeaders[5];
	//*splitHeaders = decipherHeader(machineId+commandSent+requestId+userId+timeStamp);
	//printf(*string);

    // Check for input errors
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <Listening Port>" << endl;
        exit(1);
    }
    
    // Initilize the server
    addrSize = initServer(serverSock, atoi(argv[1]));
    
    // Clear the socket sets    
    FD_ZERO(&recvSockSet);

    // Add the listening socket to the set
    FD_SET(serverSock, &recvSockSet);
    maxDesc = std::max(maxDesc, serverSock);

	// Adds any child sockets to the set
	for (i = 0; i < MAXCLIENTS; i++) {
		sockDesc = clientSocket[i];
		// If valid descriptor then add to received list
		if (sockDesc > 0)
			FD_SET(sockDesc, &tempRecvSockSet);
		// If highest file descriptor
		if (sockDesc > maxDesc)
			maxDesc = sockDesc;
	}
    
    // Run the server until a "terminate" command is received)
    while (!terminated) {
        // copy the receive descriptors to the working set
        memcpy(&tempRecvSockSet, &recvSockSet, sizeof(recvSockSet));
        
        // Select timeout has to be reset every time before select() is
        // called, since select() may update the timeout parameter to
        // indicate how much time was left.
        selectTime = timeout;
        int ready = select(maxDesc + 1, &tempRecvSockSet, NULL, NULL, &selectTime);
        if ((ready < 0) && (errno != EINTR))
        {
            cout << "select() failed" << endl;
            break;
        }

        // First, process new connection request, if any.
        if (FD_ISSET(serverSock, &tempRecvSockSet))
        {
            // set the size of the client address structure
             int size = sizeof(clientAddr);
			
            // Establish a connection
			// Maybe change clientAddr -> serverAddr and size -> addrSize
			if ((clientSock = accept(serverSock, (struct sockaddr *) &clientAddr, &size)) < 0) {
				cout << "accept() error" << endl;
				break;
			}
            cout << "Accepted a connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port << endl;
            
			// Send greeting message to client
			if (send(clientSock, message, strlen(message), 0) != strlen(message))
				cout << "send() error" << endl;

			puts("Sent greeting to client");

            // Add the new connection to the receive socket set
            FD_SET(clientSock, &recvSockSet);
            maxDesc = std::max(maxDesc, clientSock);

			// Add new socket to list
			for (i = 0; i < MAXCLIENTS; i++) {
				if (clientSocket[i] == 0) {
					clientSocket[i] = clientSock;
					cout << "Adding " << i << " to the list" << endl;
					break;
				}
			}
        }
        
        // Then process messages waiting at each ready socket
        else
            processSockets(tempRecvSockSet);
    }

    // Close the connections with the client
    for (int sock = 0; sock <= maxDesc; sock++)
    {
        if (FD_ISSET(sock, &recvSockSet))
            close(sock);
    }
    
    // Close the server sockets
    close(serverSock);
}

int initServer(int& serverSock, int port)
{
    struct sockaddr_in serverAddr;   // address of the server

    // Create a TCP socket
    // * AF_INET: using address family "Internet Protocol address"
    // * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
    // * IPPROTO_TCP: TCP protocol
    if ((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        cout << "socket() failed" << endl;
        exit(1);
    }
    
    // Free up the port before binding
    // * sock: the socket just created
    // * SOL_SOCKET: set the protocol level at the socket level
    // * SO_REUSEADDR: allow reuse of local addresses
    // * &yes: set SO_REUSEADDR on a socket to true (1)
    // * sizeof(int): size of the value pointed by "yes"
    int yes = 1;
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes)) < 0) {
        cout << "setsockopt() failed" << endl;
        exit(1);
    }
    
    // Initialize the server information
    // Note that we can't choose a port less than 1023 if we are not privileged users (root)
    memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
    serverAddr.sin_family = AF_INET;                    // Use Internet address family
    serverAddr.sin_port = htons(port);                  // Server port number
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // Any incoming interface
    
    // Bind to the local address
    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "bind() failed" << endl;
        exit(1);
    }
	cout << "Listener:" << port << endl;
    
    // Listen for connection requests
    if (listen(serverSock, MAXPENDING) < 0)
    {
        cout << "listen() failed" << endl;
        exit(1);
    }

	// Accepts the incoming connection
	int addrSize = sizeof(serverAddr);
	puts("Server initialization complete.\nWaiting on a connection...");

	return addrSize;
}

void processSockets (fd_set readySocks)
{
    char* buffer = new char[BUFFERSIZE];       // Buffer for the message from the server
    int size =0;                                    // Actual size of the message 
    
    // Loop through the descriptors and process
    for (int sock = 0; sock <= maxDesc; sock++)
    {
        if (!FD_ISSET(sock, &readySocks))
            continue;
        
        // Clear the buffers
        memset(buffer, 0, BUFFERSIZE);

        // Receive data from the client
        receiveData(sock, buffer, size);
        memset(buffer, 0, BUFFERSIZE);
        // Echo the message back to the client
       // sendData(sock, buffer, size);        
    }
    
    delete[] buffer;
}

void receiveData (int sock, char* inBuffer, int& size)
{
    // Receive the message from client
   // size = recv(sock, (char *) inBuffer, BUFFERSIZE, 0);
    // Check for connection close (0) or errors (< 0)
	size = 0;
	do {
		size = recv(sock, (char*)inBuffer, BUFFERSIZE, 0);
	} while( size == BUFFERSIZE);

				
	 if (size <= 0)
    {
        cout << "recv() failed, or the connection is closed. " << endl;
        FD_CLR(sock, &recvSockSet);
        
        // Update the max descriptor
        while (FD_ISSET(maxDesc, &recvSockSet) == false)
              maxDesc -= 1;
        return; 
    }
	handleRequest(sock, string(inBuffer));
  
	// Handles the string
}

void sendData (int sock, char* buffer, int size)
{
	
    int bytesSent = 0;                   // Number of bytes sent
    // Sent the data
    bytesSent += send(sock, (char *) buffer + bytesSent, size - bytesSent, 0);
    if (bytesSent < 0 || bytesSent != size)
    {
        cout << "error in sending" << endl;
        return;
    }
    
    if (strncmp(buffer, "terminate", 9) == 0)
        terminated = true;
}

void handleRequest(int sock, string request){
	serverHeader(request);
	cout<<request<<endl;
	string username = request.substr(72,12);
	username.erase(remove(username.begin(),username.end(),' '),username.end());
	if(request.compare( 40, 5, "login",0,5)==0){
		string password = request.substr(92,(request.length()-92));
		User newlyLoggedIn = dbMan.getUser(username);
		if(password.compare(newlyLoggedIn.getPassword())==0){
			header.append( "success");
		}
		else{
			header.append("failure");
		}

	} else if (request.compare(40,10, "friendlist",0,10)==0){
		string buff = dbMan.getFriendList(username);
		header.append(buff);
	} else if(request.compare(40, 8, "chatlist", 0, 8)==0) {
		string buff = dbMan.getChatList(username);
		cout<<buff<<endl;
		header.append(buff);
	} else if(request.compare(40, 4, "chat", 0, 4) == 0) {
		string body = request.substr(92);
		stringstream b (body);
		string chatId;
		string message;
		getline(b, chatId);
		getline(b, message);

		string chat = chatMan.addMessage(chatId, username, message);
	}
	
	sendData(sock, (char*)&header[0],header.length());

}

void serverHeader (string request){
	commandSent = request.substr(40,12);
	requestId = request.substr(52,20);
    getTimeStamp();
    header = commandSent + requestId +timeStamp;
}

void getTimeStamp() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%m%d%H%M",timeinfo);
    std::string str(buffer);

    timeStamp = str;
}

