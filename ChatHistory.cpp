//NOTCOMPLETED
#include "ChatHistory.h"

int ChatHistory::channelIDCounter=0;


ChatHistory::ChatHistory(string filename, string access, string type):FileInfo(filename,access){
	channelType = type;
	channelID = ++channelIDCounter;
}