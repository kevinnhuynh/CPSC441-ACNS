/*
*this main sets up the database of users and chathistories, only run if you need to create databases or, if you want to
* start the database overagain from the begining, delete .db files, and changethe SaveChatHistoryCounter to 0
*/

#include "User.h"
#include "DatabaseManager.h"
#include "ChatManager.h"
#include "ChatHistory.h"
#include "FileInfo.h"


#if 1

int main(){
	//create a Database Manager and Chat Manager
	DatabaseManager myManager;
	ChatManager myChatManager;
	//create 10 users with unique names
	User firstUser("Liam", "Liampassword", "khbjh179@gmail.com");
    User secondUser("Noah","Noahpassword","khbjh179@gmail.com");
	User thirdUser("Logan","Loganpassword","khbjh179@gmail.com");
	User fourthUser("James","Jamespassword","khbjh179@gmail.com");
	User fifthUser("Oliver","Oliverpassword","khbjh179@gmail.com");
	User sixthUser("Emma","Emmapassword","khbjh179@gmail.com");
	User seventhUser("Ava","Avapassword","khbjh179@gmail.com");
	User eighthUser("Olivia","Oliviapassword","khbjh179@gmail.com");
	User ninthUser("Isabella","Isabellapassword","khbjh179@gmail.com");
	User tenthUser("Amelia","Ameliapassword","khbjh179@gmail.com");
	
	//store users in database
	myManager.storeUser(firstUser);
    myManager.storeUser(secondUser);
	myManager.storeUser(thirdUser);
	myManager.storeUser(fourthUser);
	myManager.storeUser(fifthUser);
	myManager.storeUser(sixthUser);
	myManager.storeUser(seventhUser);
	myManager.storeUser(eighthUser);
	myManager.storeUser(ninthUser);
	myManager.storeUser(tenthUser);
	
	//create some Friendships
	myManager.addFriend("Liam", "Logan");
	myManager.addFriend("Liam", "Oliver");
	myManager.addFriend("Logan", "Amelia");
	myManager.addFriend("Emma", "Isabella");
	myManager.addFriend("Isabella", "James");
	myManager.addFriend("Noah", "Oliver");
	myManager.addFriend("Ava", "Olivia");
	myManager.addFriend("Logan", "James");
	myManager.addFriend("Ava", "James");
	myManager.addFriend("Amelia", "Liam");
	myManager.addFriend("Isabella", "Ava");
	myManager.addFriend("Emma", "Noah");
	myManager.addFriend("Isabella", "Olivia");
	myManager.addFriend("Amelia", "James");
	
    //myManager.printDatabaseContents();
	
	//set Up some Chathistories
	//add Chathistories to users
	string chatId = myChatManager.createChat("Liam","private");
	string newChatId = myChatManager.addAccess(chatId, "Logan");
	myManager.addChatId("Liam", newChatId);
	myManager.addChatId("Logan", newChatId);
	
	chatId = myChatManager.createChat("Liam","private");
	newChatId = myChatManager.addAccess(chatId, "Oliver");
	myManager.addChatId("Liam", newChatId);
	myManager.addChatId("Oliver", newChatId);
	
	chatId = myChatManager.createChat("Logan","private");
	newChatId = myChatManager.addAccess(chatId, "Amelia");
	myManager.addChatId("Logan", newChatId);
	myManager.addChatId("Amelia", newChatId);
	
	chatId = myChatManager.createChat("Emma","private");
	newChatId = myChatManager.addAccess(chatId, "Isabella");
	myManager.addChatId("Emma", newChatId);
	myManager.addChatId("Isabella", newChatId);
	
	chatId = myChatManager.createChat("Isabella","private");
	newChatId = myChatManager.addAccess(chatId, "James");
	myManager.addChatId("Isabella", newChatId);
	myManager.addChatId("James", newChatId);
	
	chatId = myChatManager.createChat("Noah","private");
	newChatId = myChatManager.addAccess(chatId, "Oliver");
	myManager.addChatId("Noah", newChatId);
	myManager.addChatId("Oliver", newChatId);
	
	chatId = myChatManager.createChat("Ava","private");
	newChatId = myChatManager.addAccess(chatId, "Olivia");
	myManager.addChatId("Ava", newChatId);
	myManager.addChatId("Olivia", newChatId);
	
	chatId = myChatManager.createChat("Logan","private");
	newChatId = myChatManager.addAccess(chatId, "James");
	myManager.addChatId("Logan", newChatId);
	myManager.addChatId("James", newChatId);
	
	chatId = myChatManager.createChat("Ava","private");
	newChatId = myChatManager.addAccess(chatId, "James");
	myManager.addChatId("Ava", newChatId);
	myManager.addChatId("James", newChatId);
	
	chatId = myChatManager.createChat("Amelia","private");
	newChatId = myChatManager.addAccess(chatId, "Liam");
	myManager.addChatId("Amelia", newChatId);
	myManager.addChatId("Liam", newChatId);
	
	chatId = myChatManager.createChat("Isabella","private");
	newChatId = myChatManager.addAccess(chatId, "Ava");
	myManager.addChatId("Isabella", newChatId);
	myManager.addChatId("Ava", newChatId);
	
	chatId = myChatManager.createChat("Emma","private");
	newChatId = myChatManager.addAccess(chatId, "Noah");
	myManager.addChatId("Emma", newChatId);
	myManager.addChatId("Noah", newChatId);
	
	chatId = myChatManager.createChat("Isabella","private");
	newChatId = myChatManager.addAccess(chatId, "Olivia");
	myManager.addChatId("Isabella", newChatId);
	myManager.addChatId("Olivia", newChatId);
	
	chatId = myChatManager.createChat("Amelia","private");
	newChatId = myChatManager.addAccess(chatId, "James");
	myManager.addChatId("Amelia", newChatId);
	myManager.addChatId("James", newChatId);
	
	//add chatIds to users
	

	
//    myManager.printDatabaseContents();
	  myChatManager.printDatabaseContents();
	
	
}


#endif



