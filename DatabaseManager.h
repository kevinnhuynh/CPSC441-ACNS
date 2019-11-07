
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
	string convertStringListToString(list<string> theList);
	list<string> convertStringToStringList(string theString);
	//static int formatUser(void* data, int argc, char** argv, char** azColName);
	
	

	
	public:
	static User result;
	DatabaseManager();
	void storeUser(User user);
	User getUser(string userName);
	void removeChatId(string username, string chatId);
	void addChatId(string username, string catId);
	void addMachineId(string);
	
	
	
	
	
};

#endif
