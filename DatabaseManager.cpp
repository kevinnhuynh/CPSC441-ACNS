//database code adapted from https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/ accessed November 6
//http://www.codebind.com/cprogramming/sqlite-cc-create-table-sqlite-database-using-cc/


#include "DatabaseManager.h"

using namespace std;

User DatabaseManager::result = User();

static int formatUser(void* data, int argc, char** argv, char** azColName)
{ 
	
   
    DatabaseManager::result = User(argv[0], argv[1], argv[2]);
     
 
    return 0; 
} 

DatabaseManager::DatabaseManager(){
	actionStatus = 0;
	err_message = NULL;
	initializeTables();
	
}

void DatabaseManager::initializeTables(){
	actionStatus = sqlite3_open("user.db", &DB);
   
    if (actionStatus) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        exit (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;
	
	
        string sql = "DROP TABLE IF EXISTS USERS"
                        " CREATE TABLE USERS("
                        "USERNAME TEXT PRIMARY KEY      NOT NULL,"
                        "PASSWORD       TEXT    NOT NULL,"
                        "EMAIL          TEXT    NOT NULL,"
                        "FRIENDLIST     TEXT    ,"
                        "MACHINEID      TEXT    );";
	
	actionStatus = sqlite3_exec(DB, sql.c_str(), 0, 0, &err_message);
	  if (actionStatus != SQLITE_OK ) {
    cout<<"SQL error: "<< err_message<<endl;
    sqlite3_free(err_message);
    sqlite3_close(DB);   
  } else {
    cout<< "Table STUDENTS created successfully"<<endl;
  }
  
    sqlite3_close(DB);
}

void DatabaseManager::storeUser(User user){
	actionStatus = sqlite3_open("user.db", &DB);
   
    if (actionStatus) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        exit (-1);
    }	
	string sql("INSERT INTO USER VALUES("+user.getUserName()+", "+user.getPassword()+", "+user.getEmail()+", "+convertStringListToString(user.getFriendList())+";");
	actionStatus = sqlite3_exec(DB, sql.c_str(), NULL, 0, &err_message);
	
	sqlite3_close(DB);
}

User DatabaseManager::getUser(string user){
	actionStatus = sqlite3_open("user.db", &DB);
   
    if (actionStatus) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        exit (-1);
    }	
	string sql("SELECT FROM USER WHERE USERNAME = "+user+";");
	actionStatus = sqlite3_exec(DB, sql.c_str(), formatUser, 0, &err_message);
	sqlite3_close(DB);
	return result;
}

string DatabaseManager::convertStringListToString(list<string>theList){
	list<string>::iterator it;
	string convertedList = "";
	for (it = theList.begin();it !=theList.end();++it){
			convertedList+=((*it)+" ");	
	}
	return convertedList;
}

list<string> DatabaseManager::convertStringToStringList(string theString){
	list<string> temporary;
	string intermediate;
	stringstream check(theString);
	 while(getline(check, intermediate, ' ')) 
    { 
        temporary.push_front(intermediate); 
    } 
	
}
