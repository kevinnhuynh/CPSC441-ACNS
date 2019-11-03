#ifndef EMAILSERVER_H
#define EMAILSERVER_H
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

using namespace std;
class EmailServer{
	private:
	CURL *curl;
	CURLcode res;
	const char *data;
	std::string formatEmailBody(std::string address, std::string content);

	public:
	 void sendEmail(std::string address, std::string content);
	 
};


#endif
