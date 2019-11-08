
# Makefile for compiling Server

#***********************************************************

#Variables

#**************************************************************

all: Server

Server: Server.o EmailServer.o User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o 
	g++ --std=c++11 -o Server Server.o EmailServer.o User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o -lsqlite3 -lcurl

Client: TCPClient.o
	g++ --std=c++11 -o Client TCPClient.o

SetUpDatabase:
	g++ --std=c++11 -o Server User.o DatabaseManager.o ChatManager.o ChatHistory.o fileInfo.o ChatSystemDemoSetup.o -lsqlite3

#ADD MORE COMPILE COMMANDS HERE FOR SERVER

TCPClient.o: TCPClient.cpp
	g++ --std=c++11 -c TCPClient.cpp

User.o: User.cpp
	g++ --std=c++11	-c User.cpp

DatabaseManager.o: DatabaseManager.cpp
	g++ --std=c++11 -c DatabaseManager.cpp 
	
ChatManager.o: ChatManager.cpp
	g++ --std=c++11 -c ChatManager.cpp
	
ChatHistory.o: ChatHistory.cpp
	g++ --std=c++11 -c ChatHistory.cpp
	
FileInfo.o: FileInfo.cpp
	g++ --std=c++11 -c FileInfo.cpp

ChatSystemDemoSetup.o: ChatSystemDemoSetup.cpp
	g++ --std=c++11 -c ChatSystemDemoSetup.o ChatSystemDemoSetup.o -lsqlite3

EmailServer.o: EmailServer.cpp
	g++ -c EmailServer.cpp

Server.o: Server.cpp
	g++ --std=c++11 -c Server.cpp

clean:
	rm *.o Server
