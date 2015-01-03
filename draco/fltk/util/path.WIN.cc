
#ifdef _WIN32


#include "path.h"

#include <windows.h>
//#include <tchar.h>
#include <strsafe.h>
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
	string s(*this);
	for(size_t i=s.find('/'); i != npos; i=s.find('/'))
		s.replace(i, 1, 1, '\\');
	return s;
}

list<string> Path::dirList(bool includeHidden) const {
	list<string> entries;
	WIN32_FIND_DATA data;
	cout << native().c_str() << endl;
	TCHAR dirPath[MAX_PATH];
	StringCchCopy(dirPath, MAX_PATH, native().c_str());
	StringCchCat(dirPath, MAX_PATH, TEXT("*"));
	HANDLE dir = FindFirstFile(native().c_str(), &data);
	if (dir == INVALID_HANDLE_VALUE)
		return entries;
	cout << "Huh?" << endl;
	struct dirent *entry;
	while (FindNextFile(dir, &data) != 0 || GetLastError() != ERROR_NO_MORE_FILES) {
		entries.push_back(data.cFileName);
	}
	FindClose(dir);
	return entries;
}
string Path::fileType() const {
	return "";
}


#endif // _WIN32
