#include "User.h"
//string manipulation adapted from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
#if 0
User::User (const User&src){
        userName = src.userName;
        password = src.password;
        email = src.password;
        friendList = src.friendList;

}
#endif

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
#if 0
User User::operator = (const User&src){
        userName = src.userName;
        password = src.password;
        email = src.password;
        friendList = src.friendList;

}
#endif
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

string User::toString(){

     string user ="Username: "+userName+"\n password: "+password+ "\n email: "+email+"\n";
     list<string>::iterator it;
                for (it = friendList.begin();it !=friendList.end();++it){
             user+=((*it)+" ");
        }
                return user;
}

void User::setFriendList(list<string>theList){
        friendList=theList;

}

string User::convertStringListToString(list<string>theList){
        list<string>::iterator it;
        string convertedList = "";
        for (it = theList.begin();it !=theList.end();++it){
                        convertedList+=((*it)+"\n");
        }
        return convertedList;
}

list<string> User::convertStringToStringList(string theString){
        list<string> temporary;
        string intermediate;
        stringstream check(theString);
         while(getline(check, intermediate, '\n'))
    {
        temporary.push_front(intermediate);
    }
return temporary;
}
