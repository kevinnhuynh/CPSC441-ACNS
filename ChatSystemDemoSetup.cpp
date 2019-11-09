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
	myChatManager.createChat("Liam","private");
	myChatManager.addAccess("1", "Logan");
	myChatManager.createChat("Liam","private");
	myChatManager.addAccess("2", "Oliver");
	myChatManager.createChat("Logan","private");
	myChatManager.addAccess("3", "Amelia");
	myChatManager.createChat("Emma","private");
	myChatManager.addAccess("4", "Isabella");
	myChatManager.createChat("Isabella","private");
	myChatManager.addAccess("5", "James");
	myChatManager.createChat("Noah","private");
	myChatManager.addAccess("6", "Oliver");
	myChatManager.createChat("Ava","private");
	myChatManager.addAccess("7", "Olivia");
	myChatManager.createChat("Logan","private");
	myChatManager.addAccess("8", "James");
	myChatManager.createChat("Ava","private");
	myChatManager.addAccess("9", "James");
	myChatManager.createChat("Amelia","private");
	myChatManager.addAccess("10", "Liam");
	myChatManager.createChat("Isabella","private");
	myChatManager.addAccess("11", "Ava");
	myChatManager.createChat("Emma","private");
	myChatManager.addAccess("12", "Noah");
	myChatManager.createChat("Isabella","private");
	myChatManager.addAccess("13", "Olivia");
	myChatManager.createChat("Amelia","private");
	myChatManager.addAccess("14", "James");
	
	//add chatIds to users
	myManager.addChatId("Liam", "1");
	myManager.addChatId("Logan", "1");
	myManager.addChatId("Liam", "2");
	myManager.addChatId("Oliver", "2");
	myManager.addChatId("Logan", "3");
	myManager.addChatId("Amelia", "3");
	myManager.addChatId("Emma", "4");
	myManager.addChatId("Isabella", "4");
	myManager.addChatId("Isabella", "5");
	myManager.addChatId("James", "5");
	myManager.addChatId("Noah", "6");
	myManager.addChatId("Oliver", "6");
	myManager.addChatId("Ava", "7");
	myManager.addChatId("Olivia", "7");
	myManager.addChatId("Logan", "8");
	myManager.addChatId("James", "8");
	myManager.addChatId("Ava", "9");
	myManager.addChatId("James", "9");
	myManager.addChatId("Amelia", "10");
	myManager.addChatId("Liam", "10");
	myManager.addChatId("Isabella", "11");
	myManager.addChatId("Ava", "11");
	myManager.addChatId("Emma", "12");
	myManager.addChatId("Noah", "12");
	myManager.addChatId("Isabella", "13");
	myManager.addChatId("Olivia", "13");
	myManager.addChatId("Amelia", "14");
	myManager.addChatId("James", "14");
	
    myManager.printDatabaseContents();

	
	
}


#endif



