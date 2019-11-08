/*
 * A simple TCP server that echos messages back to the client.
 * This server works with only a single client.  With a simple modification, it can take more clients.
 * For use in CPSC 441 lectures
 * Instructor: Prof. Mea Wang
 */
 
#include <Server.h>
#include <EmailServer.cpp>
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>

using namespace std;

const int BUFFERSIZE = 1024;   // Size the message buffers
const int MAXPENDING = 10;    // Maximum pending connections
const int maxClient = 100;

int main(int argc, char *argv[]) {
    int serverSock;                  // server socket descriptor
    int clientSock;                  // client socket descriptor
	int addressSize;
	int clientSocket[10];
	int activity;
	int valueRead;
	int sockDesc;
	int maxSockDesc;
	int i;

	fd_set readfds;

    struct sockaddr_in clientAddr;   // address of the client
    
    char inBuffer[BUFFERSIZE];       // Buffer for the message from the server
    int bytesRecv, bytes;            // Number of bytes received
    int bytesSent;                   // Number of bytes sent
       
    // Check for input errors
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <Listening Port>" << endl;
        exit(1);
    }

	for (i = 0; i < maxClient; i++)
		clientSocket[i] = 0;
    
	// Create a TCP socket
// * AF_INET: using address family "Internet Protocol address"
// * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
// * IPPROTO_TCP: TCP protocol
	if ((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
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
	if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
	{
		cout << "setsockopt() failed" << endl;
		exit(1);
	}

	// Initialize the server information
	// Note that we can't choose a port less than 1023 if we are not privileged users (root)
	memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
	serverAddr.sin_family = AF_INET;                    // Use Internet address family
	serverAddr.sin_port = htons(atoi(argv[1]));         // Server port number
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);		// Any incoming interface

	// Bind to the local address
	if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		cout << "bind() failed" << endl;
		exit(1);
	}
	printf("Port: %d \n", port);

	// Listen for connection requests
	if (listen(serverSock, MAXPENDING) < 0)
	{
		cout << "listen() failed" << endl;
		exit(1);
	}

	addressSize = sizeof(serverAddr);
	puts("Waiting for connections..");

	/*
    // set the size of the client address structure
    unsigned int size = sizeof(clientAddr);
	
    // Waiting for connection requests
    if ((clientSock = accept(serverSock, (struct sockaddr *) &clientAddr, &size)) < 0)
    {
        cout << "accept() failed" << endl;
        exit(1);
    }
    
    // The server will be blocked until a client is connected to it.
    cout << "Accepted a connection from " << inet_ntoa(clientAddr.sin_addr) << endl;*/
    
    // Start communication with the client (terminate when receive a "terminate" command)
    while (strncmp(inBuffer, "terminate", 9) != 0)
    {
		FD_ZERO(&readfds);

		FD_SET(serverSock, &readfds);
		max_sd = serverSock;

		for (i = 0; i < maxClient; i++) {
			sockDesc = client_socket[i];
			
			if (sockDesc > 0)
				sockDesc, &readfds;

			if (sockDesc > maxSockDesc)
				maxSockDesc = sockDesc;
		}

		activity = select(maxSockDesc + 1, &readfds, NULL, NULL, NULL);

		if ((activity < 0) && (errno != EINTR))
			printf("select() error");

		if (FD_ISSET(serverSock, &readfds)) {
			if ((clientSock = accept(serverSock, (struct sockaddr *)&serverAddr, (socklen_t*)&addrlen)) < 0) {
				cout << "accept() client error" << endl;
				exit(1);
			}

			printf("New connection established: IP: %s, Socket fd: %d\n" , inet_ntoa(serverAddr.sin_addr), clientSock);
			
			if (send(clientSock, getMessage(), strlen(getMessage()), 0) != str(getMessage()))
				cout << "send() message to client error" << endl;

			for (i = 0; i < maxClient; i++) {
				if (clientSocket[i] == 0) {
					clientSocket[i] = clientSock;
					printf("Adding %d to list\n", i);
					break;
				}
			}
		}

		for (i = 0; i < maxClient; i++) {
			sockDesc = clientSocket[i]

				if (FD_ISSET(sockDesc, &readfds)) {
					if ((valueRead = read(sockDesc, inBuffer, 1024)) == 0) {
						getpeername(sockDesc, (struct sockaddr*)&serverAddr, (socklen_t*)&addressSize);
						printf("Host disconnected: IP: %s, port: %d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
						close(sockDesc);
						clientSocket[i] = 0;
					}
					else {
						inBuffer[valueRead] = '\0';
						send(sockDesc, inBuffer, strlen(inBuffer), 0);
					}
			}
		}



        // Clear the buffers
        memset(&inBuffer, 0, BUFFERSIZE);

        // Receive the message from client
        bytesRecv = recv(clientSock, (char *) &inBuffer, BUFFERSIZE, 0);
 
        // Check for connection close (0) or errors (< 0)
        if (bytesRecv <= 0)
        {
            cout << "recv() failed, or the connection is closed. " << endl;
            exit(1); 
        }
        cout << "Client: " << inBuffer;
        
        // Echo the message back to the client
        bytesSent = send(clientSock, (char *) &inBuffer, bytesRecv, 0);
            
        if (bytesSent < 0 || bytesSent != bytesRecv)
        {
            cout << "error in sending" << endl;
            exit(1); 
        }
    }
    
    // Close the connection with the client
    close(clientSock);
    
    // Close the server socket
    close(serverSock);

	return 0;
}

// Deciphers the type of message in the content sent to the Server
std::string decipherMessage(std::string content) {
	// If content is a chat message
	if (content) { continue; }
	// If content is a message for an address
	if else (content == )
		// If content is a friend request / removal
}

// Sends content to address (redundant) ***
void Server::sendEmail(std::string address, std::string content) {
	EmailServer::sendEmail(address, content);
}

void sendMessages() {

}