# Makefile for compiling Server

#***********************************************************

#Variables

CXX = g++
CXXFLAGS = -Wall -lcurl

#**************************************************************

all: Server

Server: User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o 
	g++ --std=c++11 -o Server User.o DatabaseManager.o ChatManager.o ChatHistory.o FileInfo.o -lsqlite3

SetUpDatabase:
	g++ --std=c++11 -o Server User.o DatabaseManager.o ChatManager.o ChatHistory.o fileInfo.o ChatSystemDemoSetup.o -lsqlite3

#ADD MORE COMPILE COMMANDS HERE FOR SERVER

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
	g++ --std=c++11 -o ChatSystemDemoSetup.o ChatSystemDemoSetup.o -lsqlite3

clean:
	rm *.o Server
