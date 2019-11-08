# Header file for Server.cpp

#ifndef SERVER_H
#define SERVER_H

#include <iostream>


using namespace std;

class Server {
private:
	std::string decipherMessage(std::string);
	void handleFailure();
	void manageErrorQueue();
	void initServer(int socket, int port);

public:
	void sendEmail(std::string, std::string);
	//void createAccount();
	void loginAccount();
	void sendMessages();
	void sendChatHistory();
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