

#include "FileInfo.h"

using namespace std;


FileInfo::FileInfo(string filename, string access){
	this->filename = filename;
	accessIDList.push_front(access);
	
}

FileInfo::FileInfo(string filename, list<string> accessList){
	
	this->filename = filename;
	accessIDList = accessList;
	
}

FileInfo::FileInfo(const FileInfo& src){
	accessIDList=src.accessIDList;
	filename = src.filename;


}

FileInfo FileInfo::operator = (const FileInfo& rhs){
	accessIDList = rhs.accessIDList;
	filename = rhs.filename;
	return *this;
	
	
}

void FileInfo::saveFile(string fileContents){
	fileptr.open(filename.c_str(), ios::out|ios::in);
	fileptr<<fileContents;
	fileptr.close();
	
}


string FileInfo::getFile(){
	fileptr.open(filename.c_str(), ios::out|ios::in);
	string fileContents;
	string fileLine;
	while(getline(fileptr,fileLine)){
		fileContents+=fileLine+"\n";
	}
	fileptr.close();
	return fileContents;
}

bool FileInfo::checkAccess(string id){
	list<string>::iterator it;
	for (it = accessIDList.begin();it !=accessIDList.end();++it){
		if(!id.compare(*it)){
			return true;
		}
		
	}
	return false;
	
}

void FileInfo::addAccess(string access){
	accessIDList.push_front(access);
	
}

