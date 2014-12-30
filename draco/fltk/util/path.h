
#ifndef DRACO_FILE_SYSTEM_H
#define DRACO_FILE_SYSTEM_H

#include <string>

#define MAX_EXECUTABLE_PATH_LENGTH 512


class Path: public std::string {
public:
	static std::string getExePath();
	static std::string getExeDirectory();
	static std::string osToStd(const std::string &OsSpecificPath);
	static std::string stdToOs(const std::string );

private:
	static std::string exePath;
	static std::string exeDirectory;

};


#endif // DRACO_FILE_SYSTEM_H
