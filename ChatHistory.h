
#ifndef CHATHISTORY_H
#define CHATHISTORY_H
#include <string>
#include <iostream>
#include "FileInfo.h"
using namespace std;

class ChatHistory:public FileInfo{
	private:
		int channelID;
		string channelType;
		static int channelIDCounter;
	
	public:
		ChatHistory(string access, string type);
		void addMessageToChat(string message);
	
};



#endif