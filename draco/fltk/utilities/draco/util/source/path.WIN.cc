#ifdef _WIN32


#include "../path.h"

#include <Shlwapi.h>
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
	for (size_t i = find('\\'); i != npos; i = find('\\'))
		replace(i, 1, 1, '/');
}
string Path::native() const {
	string s(*this);
	for(size_t i=s.find('/'); i != npos; i=s.find('/'))
		s.replace(i, 1, 1, '\\');
	return s;
}

bool Path::exists() const {
	return PathFileExists(native().c_str());
}

bool Path::isDir() const {
	return (GetFileAttributes(native().c_str()) & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

list<string> Path::dirList(bool includeHidden) const {
	list<string> entries;
	WIN32_FIND_DATA data;
	HANDLE dir = FindFirstFile(native().c_str(), &data);
	if (dir == INVALID_HANDLE_VALUE)
		return entries; 
	do {
		if (GetLastError() == ERROR_NO_MORE_FILES)
			break;
		if (data.cFileName[0] == '.') {
			size_t nameLen = strlen(data.cFileName);
			if (nameLen < 2 || (nameLen < 3 && data.cFileName[1] == '.'))
				continue;
		}
		if (!includeHidden && data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			continue;
		entries.push_back(data.cFileName);
	} while (FindNextFile(dir, &data) != 0);
	FindClose(dir);
	return entries;
}
string Path::fileType() const {
	return "";
}


#endif // _WIN32
