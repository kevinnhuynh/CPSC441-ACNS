#include <iostream>
#include <chrono>
#include <ctime>
#include "ChatManager.h"
//NOT COMPLETED

string ChatManager::retrieveChat(string chatId, string access, string channelType){
	list<ChatHistory>::iterator it;
	
	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if((*it).getFilename() == chatId){
		 return (*it).getFile();
		}
		
	}	
}	
	
string ChatManager::addMessage(string chatId, string access, string message){
			list<ChatHistory>::iterator it;		
		
	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if((*it).getFilename() == chatId){
			break;
		}
		
	}	
		string formattedmessage="";
		formattedmessage+= (access+": "+message+"\n");
		string updatedChat = (*it).addMessageToChat(formattedmessage);
		
		return updatedChat;
	}
	

	
string ChatManager::createChat(string access, string type){

		ChatHistory temp = ChatHistory(access, type);
		privateChannels.push_front(temp);
		storeChat(temp);
		return string((privateChannels.front()).getFilename());
	
	
}

void ChatManager::addAccess(string chatId, string access){
	list<ChatHistory>::iterator it;

	for (it = privateChannels.begin();it !=privateChannels.end();++it){
		if((*it).getFilename() == chatId){
			break;
		}
		
	}	
	(*it).addAccess(access);
	updateAccessInDB((*it).getFilename(),(*it).getAccessIDList());
}

void ChatManager::saveChatHistoryCounter(){
	fstream fileptr;
	fileptr.open("SaveStaticChatHistoryCounter.txt", ios::out|ios::in);
	fileptr<<ChatHistory::channelIDCounter;
	fileptr.close();
	
}

void ChatManager::readChatHistoryCounter(){
	
	fstream fileptr;
	fileptr.open("SaveStaticChatHistoryCounter.txt", ios::out|ios::in);
	fileptr>>ChatHistory::channelIDCounter;
	fileptr.close();
}

/****************************************************************/

ChatManager::ChatManager(){
        actionStatus = 0;
        err_message = NULL;
        initializeTables();
		createChannelListFromDB();
		readChatHistoryCounter();

}

ChatManager::~ChatManager(){
        sqlite3_free(err_message);
    sqlite3_close(DB);
	saveChatHistoryCounter();
}

void ChatManager::initializeTables(){
        actionStatus = sqlite3_open("chat.db", &DB);

    if (actionStatus) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        exit (-1);
    }

    string sql = " CREATE TABLE IF NOT EXISTS CHATS("
                        "FILENAME TEXT PRIMARY KEY      NOT NULL,"
                        "CHANNELID       TEXT    NOT NULL,"
                        "CHANNELTYPE          TEXT    NOT NULL,"
                        "ACCESSIDLIST     TEXT    );";

        actionStatus = sqlite3_exec(DB, sql.c_str(), 0, 0, &err_message);
          if (actionStatus != SQLITE_OK ) {
    cout<<"SQL error: "<< err_message<<endl;

  } else {
    cout<< "Table CHATS created successfully"<<endl;
  }

}

static int getChannelList(void* data, int argc, char** argv, char** azColName){
list<ChatHistory>*temp = static_cast<list<ChatHistory>*>(data);
list<string>accessList = ChatManager::convertStringToStringList(argv[3]);
ChatHistory theChat(argv[0], argv[1], argv[2], accessList);
(*temp).push_front(theChat);
return 0;

}

void ChatManager:: createChannelListFromDB(){
	list<ChatHistory>temp;
	string sql("SELECT * FROM CHATS;");
        actionStatus = sqlite3_exec(DB, sql.c_str(), getChannelList, &temp, &err_message);
        //cout<<actionStatus<<endl;
        //cout<<"SQL error: "<<err_message<<endl;
        privateChannels = temp;
	
	
	
	
}

void ChatManager::storeChat(ChatHistory chat){

        string sql("INSERT INTO CHATS ('FILENAME', 'CHANNELID','CHANNELTYPE', 'ACCESSIDLIST') VALUES('"+chat.getFilename()+"', '"+string(chat.getChannelID())+"', '"+chat.getChannelType()+"', '"+ChatManager::convertStringListToString(chat.getAccessIDList())+"');");
        actionStatus = sqlite3_exec(DB, sql.c_str(), NULL, 0, &err_message);
		cout<<sql<<endl;
//cout<<"SQL error: "<< err_message<<endl;

}

void ChatManager::updateAccessInDB(string filename, list<string> access){
	
	string sql = "UPDATE CHATS set ACCESSIDLIST = '"+ChatManager::convertStringListToString(access)+"' where FILENAME='"+filename+"';";
    actionStatus = sqlite3_exec(DB, sql.c_str(),NULL, NULL, &err_message);

	
	
}


string ChatManager::convertStringListToString(list<string>theList){
        list<string>::iterator it;
        string convertedList = "";
        for (it = theList.begin();it !=theList.end();++it){
                        convertedList+=((*it)+"\n");
        }
        return convertedList;
}

list<string> ChatManager::convertStringToStringList(string theString){
        list<string> temporary;
        string intermediate;
        stringstream check(theString);
         while(getline(check, intermediate, '\n'))
    {
        temporary.push_front(intermediate);
    }
return temporary;
}


//this function is for testing purposes, not needed for chat system
        static int printDBContents(void* data, int argc, char** argv, char** azColName){

                 for(int i = 0; i < argc; i++) {
                const char*temp = argv[i]?argv[i]:"NULL";
        // Show column name, value, and newline
        cout << azColName[i] << ": " << temp << endl;

    }

    // Insert a newline
    cout << endl;

                return 0;

        }
        //this function is for testing purposes, not needed for chat system
void ChatManager::printDatabaseContents(){

        string sql("SELECT * FROM CHATS;");
        actionStatus = sqlite3_exec(DB, sql.c_str(), printDBContents, NULL, &err_message);

      sqlite3_free(err_message);
}
