#ifdef _WIN32


#include "../path.h"

#include <Shlwapi.h>
#include <Shlobj.h>
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

void Path::updateNativeHomeDir() {
	char path[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path) != S_OK)
		throw "Could not get home folder path.";
	_nativeHomeDir = path;
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
	return PathFileExists(native().c_str()) != 0;
}

bool Path::isDir() const {
	return (GetFileAttributes(native().c_str()) & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

list<string> Path::dirList(bool includeHidden) const {
	list<string> entries;
	WIN32_FIND_DATA data;
	string path = Path(*this).addSlash().native() +'*';
	HANDLE dir = FindFirstFile(path.c_str(), &data);
	while (dir != INVALID_HANDLE_VALUE) {
		string file = data.cFileName;
		if (file != "." && file != ".." &&
			(includeHidden || !(data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))) {
			entries.push_back(data.cFileName);
		}
		if (!FindNextFile(dir, &data)) {
			FindClose(dir);
			dir = INVALID_HANDLE_VALUE;
		}
	}
	return entries;
}
string Path::fileType() const {
	return "";
}

// TODO: unsafe buffer overflow possible!!
Path &Path::expand() {
	size_t bufSize = 512;
	char buffer[bufSize];
	PathCanonicalize(buffer, native().c_str());
	cout << buffer << endl;
	char buf2[bufSize];
	ExpandEnvironmentStrings(buffer, buf2, bufSize);
	cout << buf2 << endl;
	GetLongPathNameA(buf2, buf2, bufSize);
	cout << buf2 << endl;
	return *this;
}


#endif // _WIN32
