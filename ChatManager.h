

//NOTCOMPLETED
#ifndef CHATMANAGER_H
#define CHATMANAGER_H
#include <string>
using namespace std;

class ChatManager{
	private:
		list<ChatHistory>publicChannels;
		list<ChatHistory>privateChannels;

		
	public:
		string retrieveChat(string chatId, string access, string channelType);
		void addMessage(string chatId, string access, string message);
		string ChatHistory createChat(string access);
		void addAccess(string chatId, string access);
		
	
	
	
}

#endif