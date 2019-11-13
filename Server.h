// Header file for Server.cpp

#ifndef SERVER_H
#define SERVER_H

#include <iostream>


using namespace std;

class Server {
private:
	std::string *decipherHeader(std::string);
	void handleFailure();
	void manageErrorQueue();

public:
	void sendEmail(std::string, std::string);
	//void createAccount();
	void loginAccount(std::string);
	void sendMessages(std::string);
	void sendChatHistory(std::string);
	void logoutUser();
	void sendFriendRequest();
	void addFriend();
	void removeFriend();
	void sendFriendList();
	void sendChatList();
	void checkFile();
	void saveFile();
	void shareFile();
	void sendPublicChannelList();
	void subscribeToChannel();
	void unsubscribeToChannel();
	void manageRequestQueue();
	void manageResponseQueue();
};

#endif