//NOTCOMPLETED
#include "ChatHistory.h"

int ChatHistory::channelIDCounter=0;


ChatHistory::ChatHistory(string access, string type):FileInfo(++channelIDCounter,access){
	channelType = type;
	channelID = channelIDCounter;
}


void ChatHistory::addMessageToChat(string message){
	
  fileptr.open (filname,fstream::in | fstream::out |fstream::app);
	fileptr<<message;
	fileptr.close();
}


