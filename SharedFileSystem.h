

#ifndef SHAREDFILESYSTEM_H
#define SHAREDFILESYSTEM_H

#include <string>
#include <iostream> 
#include <list> 
#include <iterator> 
#include "FileInfo.h"

class SharedFileSystem{
	private:
		list<FileInfo>fileList;
	
	public:
		void saveFile(string filename, string fileContents, string access);
		string getFile(string filename, string access);
		string listAllSharedFiles(string chatId);
	
	
	
};



#endif