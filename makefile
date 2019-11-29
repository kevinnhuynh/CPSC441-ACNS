# Makefile for compiling Server

#***********************************************************

#Variables

#**************************************************************

all: Server Client SetUpDatabase

Server: Server.o EmailServer.o User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o
	g++ --std=c++11 -o Server Server.o EmailServer.o User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o -lsqlite3 -lcurl

Client: TCPClient.o
	g++ --std=c++11 -o Client TCPClient.o -lpthreads

SetUpDatabase: ChatSystemDemoSetup.o User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o ChatSystemDemoSetup.o
	g++ --std=c++11 -o SetUpDatabase User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o ChatSystemDemoSetup.o -lsqlite3

#ADD MORE COMPILE COMMANDS HERE FOR SERVER

TCPClient.o: TCPClient.cpp
	g++ --std=c++11 -c TCPClient.cpp -lpthreads

User.o: User.cpp
	g++ --std=c++11 -c User.cpp

DatabaseManager.o: DatabaseManager.cpp
	g++ --std=c++11 -c DatabaseManager.cpp

ChatManager.o: ChatManager.cpp
	g++ --std=c++11 -c ChatManager.cpp

ChatHistory.o: ChatHistory.cpp
	g++ --std=c++11 -c ChatHistory.cpp

FileInfo.o: FileInfo.cpp
	g++ --std=c++11 -c FileInfo.cpp

ChatSystemDemoSetup.o: ChatSystemDemoSetup.cpp
	g++ --std=c++11 -c ChatSystemDemoSetup.cpp

EmailServer.o: EmailServer.cpp
	g++ -c EmailServer.cpp

Server.o: Server.cpp
	g++  -c Server.cpp

clean:
	rm *.o