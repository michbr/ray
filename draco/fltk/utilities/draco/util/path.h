
#ifndef DRACO_FILE_SYSTEM_H
#define DRACO_FILE_SYSTEM_H

#include "EXPORT.h"
#include <list>
#include <string>


#define MAX_EXECUTABLE_PATH_LENGTH 512


class Path : public std::string {
public:
	DRACO_UTIL_API static Path exePath();
	DRACO_UTIL_API static Path exeDir();
	DRACO_UTIL_API static std::string nativeExePath();
	DRACO_UTIL_API static std::string nativeExeDir();

	DRACO_UTIL_API Path();
	DRACO_UTIL_API Path(const std::string &source);
	DRACO_UTIL_API Path(const std::string &source, size_t pos, size_t len = std::string::npos);
	DRACO_UTIL_API Path(const char *source);
	DRACO_UTIL_API Path(const char *source, size_t n);
	DRACO_UTIL_API Path(size_t n, char c);

	// the following constructor is deceptive when put into a shared library because the needed templates won't necessarily be provided (I think?)
	//template<class InputIterator>
	//DRACO_UTIL_API Path(InputIterator first, InputIterator last);
	
	DRACO_UTIL_API std::string native() const;
	DRACO_UTIL_API bool exists() const;
	DRACO_UTIL_API bool isDir() const;
	DRACO_UTIL_API std::list<std::string> dirList(bool includeHidden = false) const;
	DRACO_UTIL_API Path &clean();
	DRACO_UTIL_API Path &addSlash();

/* UNIMPLEMENTED */	DRACO_UTIL_API std::string fileType() const;	/* UNIMPLEMENTED */

private:
	static Path _exePath;
	static Path _exeDir;
	static std::string _nativeExePath;
	static std::string _nativeExeDir;

	static void updateExePaths();
	static void updateNativeExePath();

	void convert();

};


#endif // DRACO_FILE_SYSTEM_H
