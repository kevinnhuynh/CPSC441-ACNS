#include "User.h"
#include "DatabaseManager.h"

#include <iostream>
using namespace std;


#if 1

//main for testing creation, insertion and deletion of User from Database
int main(){
        User firstUser("frank", "fpassword", "femail");
        User secondUser("Heather","hpassword","hemail");
cout<<firstUser.toString()<<endl;
        DatabaseManager myManager;

        myManager.printDatabaseContents();
        myManager.storeUser(firstUser);
        myManager.storeUser(secondUser);
        myManager.printDatabaseContents();
		cout<<"testing find"<<endl;
		//cout<<DatabaseManager::result.toString()<<endl;
        User foundUser = myManager.getUser("Heather");
        cout<<foundUser.toString();
		cout<<"testing addUser"<<endl;
		
		myManager.addFriend("frank", "Samantha");
		myManager.addFriend("frank", "Jesse");
		User modifiedUser = myManager.getUser("frank");
		cout<<modifiedUser.toString()<<endl;
		
		cout<<"testing remove user\n"<<endl;
		User removedUser = myManager.getUser("frank");
		cout<<removedUser.toString()<<endl;
		myManager.removeFriend("frank", "Samantha");
		removedUser = myManager.getUser("frank");
		cout<<removedUser.toString()<<endl;
		if(!myManager.checkStatus("frank")){
		cout<<"no errors yet"<<endl;
		}
		
		cout<<"\n testing setstatus"<<endl;
		myManager.setStatus("frank",true);
		if(myManager.checkStatus("frank")){
			cout<<"frank is online";
		}
		
		cout<<"testing get friendlist"<<endl;
		cout<<myManager.getFriendList("frank");
}

#endif
