//NOTCOMPLETED
//saving objects in files adapted from https://www.geeksforgeeks.org/readwrite-class-objects-fromto-file-c/
#include "ChatHistory.h"
#include <string>

int ChatHistory::channelIDCounter=0;


ChatHistory::ChatHistory(string access, string type):FileInfo(to_string(++channelIDCounter),access){
	this->channelType = type;
	this->channelID = channelIDCounter;
}

ChatHistory::ChatHistory(string filename, string channelId, string channelType,list<string>accessList):FileInfo(filename,accessList){
	this->channelType = channelType;
	this->channelID = atoi(channelId.c_str());
	
}



string ChatHistory::addMessageToChat(string message){
	
	fileptr.open (filename,fstream::in | fstream::out |fstream::app);
	fileptr<<message;
	fileptr.close();
	return this->getFile();
}

ChatHistory::ChatHistory(const ChatHistory& rhs):FileInfo(rhs){
	this->channelID = rhs.channelID;
	this->channelType = rhs.channelType;
	
	
}

ChatHistory ChatHistory::operator = (const ChatHistory&src){
	
	FileInfo::operator=(src);
		this->channelID = src.channelID;
	this->channelType = src.channelType;
	return *this;
}




