

//NOTCOMPLETED
#ifndef CHATMANAGER_H
#define CHATMANAGER_H
#include <string>
#include "ChatHistory.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <sqlite3.h>

using namespace std;

class ChatManager{
	private:
		//list<ChatHistory>publicChannels;
		list<ChatHistory>privateChannels;
		 void initializeTables();
		 void createChannelListFromDB();
        sqlite3* DB;
        int actionStatus;
        char *err_message;
		
	public:
	/*
	*returns a string containing all the chat history for the requested chatID and whose requesting(access)
	*/
		string retrieveChat(string chatId, string access, string channelType);
		
		/*
		*adds the message to the chat and returns the updated chat
		*/
		string addMessage(string chatId, string access, string message);
		/*
		*creates a chatfile and returns a stringid of that file, also adds ChatHistory object to database
		*/
		string createChat(string access, string type);
		
		/*
		*adds a username to a file's access list, also updates ChatHistory object in database
		*/
		void addAccess(string chatId, string access);
		ChatManager();
		~ChatManager();
		/*
		*saves a chatHistory object in the database
		*/
		void storeChat(ChatHistory chat);
		
		/*
		*saves the chatHistoryCounter into a file so the filenaming system won't get messed up
		*/
		void saveChatHistoryCounter();
		
		/*
		*reads the ChtHistoryCounter from a file to preserve the filenaming system
		*/
		void readChatHistoryCounter();
		
		//next two are for formatting - changing between strings and list<string>
		static string convertStringListToString(list<string>theList);
		static list<string> convertStringToStringList(string theString);
		//for testing purposes only
		void printDatabaseContents();
		void updateAccessInDB(string filename, list<string> access);
	
	
	
};

#endif