
#ifdef _WIN32


#include "path.h"

#include <windows.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


void Path::updateNativeExePath() {
	char path[MAX_EXECUTABLE_PATH_LENGTH];
	memset(path, 0, MAX_EXECUTABLE_PATH_LENGTH);
	int length = GetModuleFileName(NULL, path, MAX_EXECUTABLE_PATH_LENGTH);
	if (length >= MAX_EXECUTABLE_PATH_LENGTH)
		throw string("Path to executable too long: ") +path +" ...";
	if (length < 1)
		throw string("Could not get executable path");
	
	_nativeExePath = path;
}

void Path::convert() {
	for(size_t i=find('\\'); i != npos; i=find('\\'))
		replace(i, 1, 1, '/');
}

string Path::native() const {
	string s(this);
	for(size_t i=s.find('/'); i != npos; i=s.find('/'))
		s.replace(i, 1, 1, '\\');
	return s;
}


#endif // _WIN32
