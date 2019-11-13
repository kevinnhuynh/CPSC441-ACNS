/*
*code adapted from  https://curl.haxx.se/libcurl/c/http-post.html/ accessed:Nov 3, 2019
*/

#include "EmailServer.h"
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;
	


std::string EmailServer::formatEmailBody(std::string address, std::string content){
	std::string body = "{\"emailAddress\": \""+address+"\", \"message\": \""+content+"\"}";
	return body;
}

void EmailServer::sendEmail(std::string address, std::string content){


	 /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
 data = (formatEmailBody(address, content)).c_str();
printf("%s",data);    
	curl_easy_setopt(curl, CURLOPT_URL, "https:/\/ja16y5um79.execute-api.us-east-2.amazonaws.com/default/EmailPython");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
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

