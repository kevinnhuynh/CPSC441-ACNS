# CPSC-441-Audio-Chat-Network-System

#makefile

The below command will setup the Database. Only run this once, if you want to reset the database to the default, remove both database files, and set the value inside the SaveStaticChatHistoryCounter.txt 

make SetUpDatabase

To run the server you must have sqlite3 installed. You can use the following command: sudo apt-get install sqlite3 libsqlite3-dev

The below command will create the server

make Server

Run the server with

./Server 9000

if using the command line, you need to use both of these options while compiling
-lsqlite3

--std=c++1


To run the email server, libcurl must be installed on the virtual machine. You can use this command:  sudo apt-get install libcurl4-nss-dev


When compiling EmailServer.cpp you must use the option -lcurl

running the command make should generate all the objects and create an executable for the server

