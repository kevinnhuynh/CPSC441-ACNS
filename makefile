# Makefile for compiling email server

#***********************************************************

#Variables

CXX = g++
CXXFLAGS = -Wall -lssl

#**************************************************************

emailServer: EmailServer.o  base64.o CSmtp.o md5.o
	$(CXX) $(CXXFLAGS) -o EmailServer EmailServer.o base64.o CSmtp.o md5.o


# the main.o target can be written more simly

EmailServer.o: EmailServer.cpp
	$(CXX) $(CXXFLAGS) -c EmailServer.cpp

base64.o: base64.cpp 
	$(CXX) $(CXXFLAGS) -c base64.cpp

md5.o: md5.cpp 
	$(CXX) $(CXXFLAGS) -c md5.cpp

CSmtp.o: CSmtp.cpp 
	$(CXX) $(CXXFLAGS) -c CSmtp.cpp
		
clean:
	rm *.o EmailServer
