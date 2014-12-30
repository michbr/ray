
#ifdef __linux__


#include "fileSystem.h"

#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


string getExePath() {
	char path[MAX_EXECUTABLE_PATH_LENGTH];
	memset(path, 0, MAX_EXECUTABLE_PATH_LENGTH);
	int length = readlink("/proc/self/exe", path, MAX_EXECUTABLE_PATH_LENGTH);
	if (length >= MAX_EXECUTABLE_PATH_LENGTH)
		throw string("Path to executable too long: ") +path +" ...";
	if (length < 1)
		throw string("Could not get executable path");
	return string(path);
}


#endif // __linux__
