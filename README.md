# CPSC-441-Audio-Chat-Network-System

#makefile
The Chat system requires these installations

sqlite3		You can use the following command: sudo apt-get install sqlite3 libsqlite3-dev
libcurl		You can use this command:  sudo apt-get install libcurl4-nss-dev

The Chat system must run on a system that uses pthreads

The below command will setup the Database. Only run this once, if you want to reset the database to the default, remove both database files, and set the value inside the SaveStaticChatHistoryCounter.txt 

make SetUpDatabase

Run the demo setup with
./SetUpDatabase

The below command will create the server

make Server

Run the server with

./Server <serverport>

The below command will create the server

make Client

Run the Client with
./Client <IPofServer> <serverport> -login <username> <password>

Below is a list of commands
./friendlist
./chatlist
./chat <chatname>
./addfriend <username>
./deletefriend <username>
./logout
(login happens automatically)

List of users and passwords
Liam		Liampassword
Noah		Noahpassword
Logan		Loganpassword
James		Jamespassword
Oliver		Oliverpassword
Emma		Emmapassword
Ava			Avapassword
Olivia		Oliviapassword
Isabella	Isabellapassword
Amelia		Ameliapassword