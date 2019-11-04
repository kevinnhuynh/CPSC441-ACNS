

//NOTCOMPLETED
#ifndef CHATMANAGER_H
#define CHATMANAGER_H

class ChatManager{
	private:
		list<ChatHistory>publicChannels;
		list<ChatHistory>privateChannels;

		
	public:
		string retrieveChat(string chatId, string access);
		void addMessage(string chatId, string access, string message);
		ChatHistory createChat(string access);
		void addAccess(string access);
		
	
	
	
}

#endif