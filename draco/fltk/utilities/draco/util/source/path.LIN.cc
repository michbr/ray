
#ifdef __linux__


#include "../path.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <pwd.h>
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

void Path::updateNativeHomeDir() {
	const char *homedir;
	if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	}
	_nativeHomeDir = homedir;
}

void Path::convert() {}

string Path::native() const {
    return string(*this);
}

bool Path::exists() const {
	struct stat buffer;
	return stat(native().c_str(), &buffer) == 0;
}

bool Path::isDir() const {
	struct stat statBuf;
	if (lstat(c_str(), &statBuf) == -1)
		return false;
	return S_ISDIR(statBuf.st_mode);
}

list<string> Path::dirList(bool includeHidden) const {
	list<string> entries;
	DIR *dir = opendir(c_str());
	if (dir == NULL)
		return entries;
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') {
			size_t nameLen = strlen(entry->d_name);
			if (!includeHidden || nameLen < 2 ||
				(nameLen < 3 && entry->d_name[1] == '.'))
				continue;
		}
		entries.push_back(entry->d_name);
	}
	closedir(dir);
	return entries;
}
string Path::fileType() const {
	return "";
}


#endif // __linux__
