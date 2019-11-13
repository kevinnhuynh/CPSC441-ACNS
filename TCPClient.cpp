/*
 * A simple TCP client that sends messages to a server and display the message
   from the server. 
 * For use in CPSC 441 lectures
 * Instructor: Prof. Mea Wang
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()
#include <string>

using namespace std;
string header;
string machineId;
string commandSent;
string userId;
string requestId;
string timeStamp;
void getTimeStamp();
void getCommand(char* outBuffer);
void getMachineId();
void headerSent (char* outBuffer);

const int BUFFERSIZE = 1024 * 10;   // Size the message buffers

int main(int argc, char *argv[])
{
    int sock;                        // A socket descriptor
    struct sockaddr_in serverAddr;   // Address of the server
    char inBuffer[BUFFERSIZE];       // Buffer for the message from the server
    int bytesRecv;                   // Number of bytes received
    
    char outBuffer[BUFFERSIZE];      // Buffer for message to the server
    int msgLength;                   // Length of the outgoing message
    int bytesSent;                   // Number of bytes sent
    
    // Check for input errors
    // login with -login <username> <password>
    if (argc != 6)
    {
        cout << "Usage: " << argv[0] << " <Server IP> <Server Port>" << endl;
        exit(1);
    }

    userId = argv[4];

    // Create a TCP socket
    // * AF_INET: using address family "Internet Protocol address"
    // * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
    // * IPPROTO_TCP: TCP protocol
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
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
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        cout << "setsockopt() failed" << endl;
        exit(1);
    }
    
    // Initialize the server information
    // Note that we can't choose a port less than 1023 if we are not privileged users (root)
    memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
    serverAddr.sin_family = AF_INET;                    // Use Internet address family
    serverAddr.sin_port = htons(atoi(argv[2]));         // Server port number
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);    // Server IP address
    
    // Connect to the server
    // * sock: the socket for this connection
    // * serverAddr: the server address
    // * sizeof(*): the size of the server address
    if (connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "connect() failed" << endl;
        exit(1);
    }
        

    cout << "Please enter a message to be sent to the server ('logout' to terminate): ";
    fgets(outBuffer, BUFFERSIZE, stdin);
    while (strncmp(outBuffer, "./logout", 8) != 0)
    {           
        msgLength = strlen(outBuffer) + 40 +12 +20 + 12 + 8;
        headerSent(outBuffer);
        header.append(outBuffer);
        strcpy(outBuffer, header.c_str());
        // Send the message to the server
        bytesSent = send(sock, (char *) &outBuffer, msgLength, 0);
        if (bytesSent < 0 || bytesSent != msgLength)
        {
            cout << "error in sending" << endl;
            exit(1); 
        }
        
        // Receive the response from the server
        bytesRecv = recv(sock, (char *) &inBuffer, sizeof(inBuffer), 0);

        char *token = strtok(outBuffer, " ");
        char *filename = strtok(NULL, "\n");


        // Check for connection close (0) or errors (< 0)
        
        if (strncmp(outBuffer, "terminate", 9) == 0)
        {

        }

        else if (bytesRecv <= 0)
        {
            cout << "recv() failed, or the connection is closed. " << endl;
            exit(1); 
        }

        else if ((strcmp(token, "get") == 0) && filename != NULL)
        {
            // cout << inBuffer;
            // cout << strcmp(inBuffer,"open() failed\n\n");
            if (strcmp(inBuffer,"open() failed\n\n") == 0)
            {
                cout << "open() failed \n";
            }
            
            else 
            {
            std::ofstream outfile (filename);

            outfile << inBuffer << std::endl;

            outfile.close();; 

            cout << "File saved in " << filename << endl;
            }
        }
        else if (strcmp(outBuffer,"list\n") == 0)
        {
            string in = string(inBuffer);
            cout << in;
        }

        else
        {
            cout << "Server: " << inBuffer;
        }
        
        // Clear the buffers
        memset(&outBuffer, 0, BUFFERSIZE);
        memset(&inBuffer, 0, BUFFERSIZE);
        cout << "Please enter a message to be sent to the server ('logout' to terminate): ";
        fgets(outBuffer, BUFFERSIZE, stdin);
    }

    // Close the socket
    close(sock);
    exit(0);
}

// get machine id
void getMachineId(){
    ifstream infile;
    infile.open("/etc/machine-id");

    // check for errors in opening the file
    if (!infile.is_open())
    {
        cout << "open() failed " << endl;
        string msg = "Error in openning file \n";
        cout << msg;
    }
    
    // Read the file line by line
    string line;
    machineId = "";
    while (getline(infile, line))
    {
        machineId += line;
    }
    machineId.resize(40,' ');
}

// get command and the requestid
void getCommand(char* outBuffer) {
    string str(outBuffer);
    if (strncmp(outBuffer, "./addfriend", 11) == 0)
    {
        commandSent = "addfriend";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./friendlist", 12) == 0)
    {
        commandSent = "friendlist";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./deletefriend", 14) == 0)
    {
        commandSent = "deletefriend";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./subscribe",11) == 0)
    {
        commandSent = "subscribe";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./unsubscribe", 13) == 0)
    {
        commandSent = "unsubscribe";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./accept", 8) == 0)
    {
        commandSent = "accept";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./chat", 6) == 0)
    {
        commandSent = "chat";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./group", 7) == 0)
    {
        commandSent = "group";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./group", 7) == 0)
    {
        commandSent = "group";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./invisible", 11) == 0)
    {
        commandSent = "invisible";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./busy", 6) == 0)
    {
        commandSent = "busy";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./normal", 8) == 0)
    {
        commandSent = "normal";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./tkgroup", 9) == 0)
    {
        commandSent = "tkgroup";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./leave", 7) == 0)
    {
        commandSent = "leave";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./join", 6) == 0)
    {
        commandSent = "join";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./reconnect", 11) == 0)
    {
        commandSent = "reconnect";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./send", 6) == 0)
    {
        commandSent = "send";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./download", 10) == 0)
    {
        commandSent = "send";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./send", 7) == 0)
    {
        commandSent = "send";
        requestId = str.substr(str.find(" ") + 1);
    }
    if (strncmp(outBuffer, "./history", 7) == 0)
    {
        commandSent = "history";
        requestId = str.substr(str.find(" ") + 1);
    }
    commandSent.resize(12,' ');
    requestId.resize(20,' ');
    userId.resize(20, ' ');
}

// reference from https://stackoverflow.com/questions/16357999/current-date-and-time-as-string
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

// header message
void headerSent (char* outBuffer){
    getMachineId();
    getCommand(outBuffer);
    getTimeStamp();
    header = machineId + commandSent + requestId + userId + timeStamp;
}
