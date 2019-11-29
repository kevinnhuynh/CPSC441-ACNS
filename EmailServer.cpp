/*
*code adapted from  https://curl.haxx.se/libcurl/c/http-post.html/ accessed:Nov 3, 2019
*/

#include "EmailServer.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

const char * data;

using namespace std;

std::string EmailServer::formatEmailBody(std::string address, std::string content){

	std::string body = "{\"emailAddress\": \""+address+"\", \"message\": \""+content+"\"}";
	return body;
}



void EmailServer::sendEmail(std::string address, std::string content){
struct curl_slist *hs=NULL;
hs = curl_slist_append(hs, "Content-Type: application/json; charset=UTF-8");
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

	 /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */

	string s = formatEmailBody(address,content);
	data = s.c_str();

	struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Accept: application/json");
    curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    curl_slist_append(headers, "charsets: utf-8");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_URL, "https:/\/ja16y5um79.execute-api.us-east-2.amazonaws.com/default/EmailPython");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	  /* size of the POST data */
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, s.size());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);



	
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

			  

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
	
}
#if 0
int main(){
	EmailServer myServer;
	myServer.sendEmail("khbjh179@gmail.com","WHHHHAAATTTT");
}
#endif