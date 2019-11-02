

#ifndef SHAREDFILESYSTEM_H
#define SHAREDFILESYSTEM_H


public class SharedFileSystem_H{
	private:
	list<FileInfo>fileList;
	
	public:
	void saveFile(string filename, string fileContents);
	string getFile(string filename);
	string listAllSharedFiles(string chatId);
	
	
	
};



#endif