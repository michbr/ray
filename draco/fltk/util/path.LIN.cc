
#ifdef __linux__


#include "path.h"
i
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


void Path::updateNativeExePath() {
	char path[MAX_EXECUTABLE_PATH_LENGTH];
	memset(path, 0, MAX_EXECUTABLE_PATH_LENGTH);
	int length = readlink("/proc/self/exe", path, MAX_EXECUTABLE_PATH_LENGTH);
	if (length >= MAX_EXECUTABLE_PATH_LENGTH)
		throw string("Path to executable too long: ") +path +" ...";
	if (length < 1)
		throw string("Could not get executable path");
	
	_nativeExePath = path;
}

void Path::convert() {}

string Path::native() const {
    return string(*this);
}

list<string> Path::dirList() const {
	list<string> entries;
	DIR *dir = opendir(c_str());
	if (dir == NULL)
		return entries;
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		entries.push_back(entry->d_name);
	}
	closedir(dir);
	return entries;
}
string Path::fileType() const {
	return "";
}


#endif // __linux__