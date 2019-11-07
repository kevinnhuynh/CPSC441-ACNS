//database code adapted from https://www.geeksforgeeks.org/sql-using-c-c-and-sqlite/ accessed November 6
//http://www.codebind.com/cprogramming/sqlite-cc-create-table-sqlite-database-using-cc/
//https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/


#include "DatabaseManager.h"

using namespace std;

//User DatabaseManager::result = User();

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
void DatabaseManager::printDatabaseContents(){

        string sql("SELECT * FROM USERS;");
        actionStatus = sqlite3_exec(DB, sql.c_str(), printDBContents, NULL, &err_message);

      sqlite3_free(err_message);
}


static int formatUser(void* data, int argc, char** argv, char** azColName)
{

        User* theUser = static_cast<User*>(data);
                list<string>tempList;
        User temp=User(argv[0], argv[1], argv[2]);
      if(argv[3]){
        //temp.setFriendList(tempList);
                temp.setFriendList(temp.convertStringToStringList(string(argv[3])));
                }
                else{
                        temp.setFriendList(tempList);
                }
        *theUser=temp;


return 0 ;
}
//puts value of status into data
static int sCheckStatus(void* data, int argc, char** argv, char** azColName){
        int * theStatus = static_cast<int*>(data);
        *theStatus = atoi(argv[0]);

}

//puts friendlist into data
static int sGetFriendList(void* data, int argc, char** argv, char** azColName){
        string * friendList= static_cast<string*>(data);
        *friendList = argv[0];

}

DatabaseManager::DatabaseManager(){
        actionStatus = 0;
        err_message = NULL;
        initializeTables();

}

DatabaseManager::~DatabaseManager(){
        sqlite3_free(err_message);
    sqlite3_close(DB);
}

void DatabaseManager::initializeTables(){
        actionStatus = sqlite3_open("user.db", &DB);

    if (actionStatus) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        exit (-1);
    }

    string sql = " CREATE TABLE IF NOT EXISTS USERS("
                        "USERNAME TEXT PRIMARY KEY      NOT NULL,"
                        "PASSWORD       TEXT    NOT NULL,"
                        "EMAIL          TEXT    NOT NULL,"
                        "FRIENDLIST     TEXT    ,"
                        "MACHINEID      TEXT    ,"
                                                "STATUS                 INT             DEFAULT 0);";

        actionStatus = sqlite3_exec(DB, sql.c_str(), 0, 0, &err_message);
          if (actionStatus != SQLITE_OK ) {
    cout<<"SQL error: "<< err_message<<endl;

  } else {
    cout<< "Table STUDENTS created successfully"<<endl;
  }


}

void DatabaseManager::storeUser(User user){

        string sql("INSERT INTO USERS ('USERNAME', 'PASSWORD','EMAIL') VALUES('"+user.getUserName()+"', '"+user.getPassword()+"', '"+user.getEmail()+"');");
        actionStatus = sqlite3_exec(DB, sql.c_str(), NULL, 0, &err_message);
cout<<sql<<endl;
//cout<<"SQL error: "<< err_message<<endl;

}

User DatabaseManager::getUser(string user){
        User foundUser;
        string sql("SELECT * FROM USERS WHERE USERNAME ='"+user+"';");
        actionStatus = sqlite3_exec(DB, sql.c_str(), formatUser, &foundUser, &err_message);
        //cout<<actionStatus<<endl;
        //cout<<"SQL error: "<<err_message<<endl;
        return foundUser;
}



string DatabaseManager::removeFriend(string username, string friendUsername){
         User temp = getUser(username);
        list<string> friends= temp.getFriendList();
        friends.remove(friendUsername);
                cout<<"before update"<<endl;
        string sql = "UPDATE USERS set FRIENDLIST = '"+temp.convertStringListToString(friends)+"' where USERNAME='"+username+"';";
        actionStatus = sqlite3_exec(DB, sql.c_str(),NULL, NULL, &err_message);
                return temp.convertStringListToString(friends);
}

string DatabaseManager::addFriend(string username, string friendUsername){
        User temp = getUser(username);
        list<string> friends= temp.getFriendList();
        friends.push_front(friendUsername);
        string sql = "UPDATE USERS set FRIENDLIST = '"+temp.convertStringListToString(friends)+"' where USERNAME='"+username+"';";
        actionStatus = sqlite3_exec(DB, sql.c_str(),NULL, NULL, &err_message);

       // cout<<"SQL error: "<< err_message<<endl;

                return temp.convertStringListToString(friends);

}

bool DatabaseManager::checkStatus(string username){
        int status;
        string sql("SELECT STATUS FROM USERS WHERE USERNAME ='"+username+"';");
    actionStatus = sqlite3_exec(DB, sql.c_str(), sCheckStatus, &status, &err_message);

        return status;

}

void DatabaseManager::setStatus(string username, bool status){
string theStatus = (status)?"1":"0";
        string sql = "UPDATE USERS set STATUS = "+theStatus+" where USERNAME='"+username+"';";
        actionStatus = sqlite3_exec(DB, sql.c_str(),NULL, NULL, &err_message);

}

string DatabaseManager::getFriendList(string username){
	string friendList;
	string sql("SELECT FRIENDLIST FROM USERS WHERE USERNAME ='"+username+"';");
    actionStatus = sqlite3_exec(DB, sql.c_str(), sGetFriendList, &friendList, &err_message);
	return friendList;
}