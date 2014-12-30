
#ifdef __apple__


#include "util/fileSystem.h"

#include <mach-o/dyld.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;


string getExePath() {
	size_t bufSize = MAX_EXECUTABLE_PATH_LENGTH;
	char path[MAX_EXECUTABLE_PATH_LENGTH];
	memset(path, 0, MAX_EXECUTABLE_PATH_LENGTH);
	int length = _NSGetExecutablePath(path, &bufSize);
	if (length >= MAX_EXECUTABLE_PATH_LENGTH)
		throw string("Path to executable too long: ") +path +" ...";
	if (length < 1)
		throw string("Could not get executable path");
	char *resolvedPath = realpath(path, NULL);
	string finalPath(resolvedPath);
	free(resolvedPath);
	return finalPath;
}


#endif // __apple__
