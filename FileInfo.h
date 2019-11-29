
#ifndef FILEINFO_H
#define FILEINFO_H
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class FileInfo{
	protected:
		list<string> accessIDList;
		fstream fileptr;
		string filename;
		
	public:
		FileInfo(string filename, string access);
		FileInfo(string filename, list<string>accessList);
		FileInfo(){}
		string getFile();
		//TODO assignment operator and destructors

		FileInfo(const FileInfo&);
		FileInfo operator =(const FileInfo& rhs);
		void saveFile(string fileContents);
		/* returns true if a file can be accessed by someone with that id*/
		bool checkAccess(string id);
		string getFilename(){return filename;}
		list<string>getAccessIDList(){return accessIDList;}
		string addAccess(string access);
	
};



#endif