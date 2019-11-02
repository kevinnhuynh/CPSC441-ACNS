#include "EmailServer.h"
#include <iostream>

EmailServer::EmailServer()
{
#define test_gmail_ssl

#if defined(test_gmail_tls)
		mail.SetSMTPServer("smtp.gmail.com",587);
		mail.SetSecurityType(/*CSmtp::*/USE_TLS);
#elif defined(test_gmail_ssl)
		mail.SetSMTPServer("smtp.gmail.com",465);
		mail.SetSecurityType(USE_SSL);
#elif defined(test_hotmail_TLS)
		mail.SetSMTPServer("smtp.live.com",25);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_aol_tls)
		mail.SetSMTPServer("smtp.aol.com",587);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_yahoo_ssl)
		mail.SetSMTPServer("plus.smtp.mail.yahoo.com",465);
		mail.SetSecurityType(USE_SSL);
#endif

		mail.SetLogin("khbjh179@gmail.com");
		mail.SetPassword("_cpsc441");
  		mail.SetSenderName("Chat System");
  		mail.SetSenderMail("khbjh179@gmail.com");
  		mail.SetReplyTo("khbjh179@gmail.com");
  		mail.SetSubject("Notification");
  		


}

void EmailServer::sendEmail(string emailAddress, string message){
	bool bError = false;
	try{
  		mail.AddRecipient(emailAddress.c_str());
  		mail.SetXPriority(XPRIORITY_NORMAL);
  		mail.SetXMailer("The Bat! (v3.02) Professional");
  		mail.AddMsgLine(message.c_str());

		mail.Send();
	}
	catch(ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		cin.get();
		bError = true;
	}
	if(!bError)
		std::cout << "Mail was sent successfully.\n";
	
}

int main(){
EmailServer myServer = EmailServer();	
myServer.sendEmail(string("khbjh179@gmail.com"), string("Hey whats up"));
	
	
	
}
