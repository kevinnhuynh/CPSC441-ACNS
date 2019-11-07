#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class User{
	
	protected:
	string userName;
	string password;
	string email;
	list<string>friendList;
	
	public:
	User(string userName, string password, string email);
	User();
	string getUserName();
	string getPassword();
	string getEmail();
	list<string>getFriendList();
	
	
	
};

#endif
