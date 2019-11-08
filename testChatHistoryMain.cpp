#include "ChatHistory.h"
#include "ChatManager.h"

#if 1

int main(){
ChatManager myManager;

myManager.createChat("frank","private");
myManager.createChat("Heather", "private");
myManager.createChat("Steven","private");

cout<<"testing to see if chat has been added to database"<<endl;
myManager.printDatabaseContents();

cout<<"testing to see if add access works"<<endl;
myManager.addAccess("1", "Heather");
myManager.printDatabaseContents();
cout<<"Testin to see if add Message works"<<endl;
cout<<myManager.addMessage("1", "frank", "yo whats up heather")<<"\n\n";
cout<<myManager.addMessage("1","Heather","not much, u?")<<"\n\n";
cout<<myManager.retrieveChat("1","frank","private");
}
#endif
