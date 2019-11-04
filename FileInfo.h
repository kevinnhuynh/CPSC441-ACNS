
#ifndef FILEINFO_H
#define FILEINFO_H
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class FileInfo{
	private:
		list<string> accessIDList;
		fstream fileptr;
		string filename;
		
	public:
		FileInfo(string filename, string access);
		string getFile();
		//TODO assignment operator and destructors

		FileInfo(const FileInfo&);
		void saveFile(string fileContents);
		/* returns true if a file can be accessed by someone with that id*/
		bool checkAccess(string id);
		string getFilename(){return filename;}
		void addAccess(string access);
	
};



#endif