#include "User.h"
//string manipulation adapted from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/

User::User(string userName, string password, string email){
	this->userName = userName;
	this->password = password;
	this->email = email;
	
}

User::User(){
	this->userName = "defaultName";
	this->password = "defaultPassword";
	this->email = "defaultEmail";
	
}


string User::getUserName(){
	return userName;
}

string User::getPassword(){
	return password;
}

string User::getEmail(){
	return email;
	
}

list<string> User::getFriendList(){
	return friendList;
	
}

int main(){
	
	
	return 0;
}
