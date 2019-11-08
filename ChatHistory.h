
#ifndef CHATHISTORY_H
#define CHATHISTORY_H
#include <string>
#include <iostream>
#include "FileInfo.h"
#include <fstream>
using namespace std;

class ChatHistory:public FileInfo{
	private:
		int channelID;
		string channelType;
		static int channelIDCounter;
	
	public:
		ChatHistory(string access, string type);
		ChatHistory(string filename, string channelId, string channelType,list<string>accessList);
		ChatHistory():FileInfo(){};
		ChatHistory(const ChatHistory& src);
		ChatHistory operator = (const ChatHistory& rhs);
		string getChannelType(){return channelType;}
		string getChannelID(){return to_string(channelID);}
		
		/*
		*saves a message to the chat file and returns the chat
		*/
		string addMessageToChat(string message);
		
	
};



#endif