#include "SharedFileSystem.h"

using namespace std; 

void SharedFileSystem::saveFile(string filename, string fileContents, string access){
	FileInfo temp = FileInfo(filename, access);
	temp.saveFile(fileContents);
	fileList.push_front(temp);
}

string SharedFileSystem::getFile(string filename, string access){
	list<FileInfo>::iterator it;
	for (it = fileList.begin();it !=fileList.end();++it){
		if(filename.compare((*it).getFilename())){
		if((*it).checkAccess(access)){
			return (*it).getFile();
		}
		return NULL;
		}
		
	}
	return NULL;
}

string SharedFileSystem::listAllSharedFiles(string chatId){
	list<FileInfo>::iterator it;
	string sharedFiles="";
	for (it = fileList.begin();it !=fileList.end();++it){
		if((*it).checkAccess(chatId)){
			sharedFiles+=((*it).getFilename() + "\n");
		}
			
	}
	return sharedFiles;
}


int main(){
	
	return 0;
}