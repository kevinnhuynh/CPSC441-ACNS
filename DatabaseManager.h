#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <list>

#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <sqlite3.h>
#include "User.h"
using namespace std;

class DatabaseManager{
        private:
        void initializeTables();
        sqlite3* DB;
        int actionStatus;
        char *err_message;
        //User formatUser(void* data, int argc, char** argv, char** azColName);




        public:
        //static User result;
        DatabaseManager();
        ~DatabaseManager();
		/*
		* stores a user in the database
		*/
        void storeUser(User user);
		
		/*
		*retrieves a user based on username
		*/
        User getUser(string userName);
		
        /*
		*adds a friend's username to a users friend list and returns the updated friend list as a string
		*/
		string addFriend(string username, string friendUsername);
		
		/*
		*removes a friend's username from a user's friend list and returns the updated friend list as a string
		*/
        string removeFriend(string username, string friendUsername);
		
		/*
		*NOT IMPLEMENTED YET, ASSIGNMENT 4
		*/
	   void addMachineId(string);
	   
		/*
		*check if a user is online or not
		*/
		bool checkStatus(string username);
		
		
		/*
		*set a user status to offline or online (when a user is added to the database
		*their status is default set to 0, The server must set it to online and offline);
		*/
		void setStatus(string username, bool status);

		
		/*
		* returns a string of a user's friend lists with each friend's usernme seperated by /n
		*/
		string getFriendList(string username);
		
        //this is for testing purposes
        void printDatabaseContents();





};

#endif
