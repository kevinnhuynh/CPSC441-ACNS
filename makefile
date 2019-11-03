# Makefile for compiling email server

#***********************************************************

#Variables

CXX = g++
CXXFLAGS = -Wall -lcurl

#**************************************************************

Server: EmailServer.o
	$(CXX) $(CXXFLAGS) -o Server EmailServer.o 



#ADD MORE COMPILE COMMANDS HERE FOR SERVER

# the EmailServer.o target created here

EmailServer.o: EmailServer.cpp
	$(CXX) $(CXXFLAGS) -c EmailServer.cpp

clean:
	rm *.o EmailServer
