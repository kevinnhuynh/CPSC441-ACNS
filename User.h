#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
//#include <bits/stdc++.h>


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
        //User operator=(const User&src);
        //User(const User&src);
        string getUserName();
        string getPassword();
        string getEmail();
        list<string>getFriendList();
        void setFriendList(list<string>theList);
        //this function is for testing putposes
        string toString();
        string convertStringListToString(list<string> theList);
		list<string> convertStringToStringList(string theString);


};

#endif
