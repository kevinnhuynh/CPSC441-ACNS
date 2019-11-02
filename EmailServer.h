#ifndef _EMAILSERVER_H
#define _EMAILSERVER_H

#include "CSmtp.h"
class EmailServer{
	private:
	CSmtp mail;
	public:
	EmailServer();
	void sendEmail(string emailAddress, string message);
	
	
};

#endif