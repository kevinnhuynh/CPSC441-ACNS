#include "ChatManager.h"
//NOT COMPLETED

string ChatManager::retrieveChat(string chatId, string access, string channelType){
	list<ChatHistory>::iterator it;
	if(channelType.compare("public"){
	for (it = publicChannels.begin();it !=publicChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
		 return (*it).getFile();
		}
		
	}
	}
	else{
	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
		 return (*it).getFile();
		}
		
	}	
	}
}	
	
	void addMessage(string chatId, string access, string message){
			list<ChatHistory>::iterator it;		
		if(channelType.compare("public"){
	for (it = publicChannels.begin();it !=publicChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
			break;
		}
		
	}
	}
	else{
	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
			break;
		}
		
	}	
		(*it).addMessageToChat(message);
		
		
	}
	

	
string ChatManager::createChat(string access, string type){
	if(type.compare("public")){
		publicChannels.push_front(ChatHistory(access,type));
		return string((publicChannels.front()).channelID);
	}
	else{
		privateChannels.push_front(ChatHistory(access, type));
		return string((privateChannels.front()).channelID);
	}
	
}

void ChatManager::addAccess(string chatId, string access){
		for (it = publicChannels.begin();it !=publicChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
			break;
		}
		
	}
	}
	else{
	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if(*(it).channelID == atoi(chatId)){
			break;
		}
		
	}	
	(*it).addAccess(access);
	
	
}
