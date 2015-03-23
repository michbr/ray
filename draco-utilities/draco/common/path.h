
#ifndef DRACO_FILE_SYSTEM_H
#define DRACO_FILE_SYSTEM_H

#include "EXPORT.h"
#include <vector>
#include <string>


#define MAX_EXECUTABLE_PATH_LENGTH 512


class Path : public std::string {
public:
	DRACO_COMMON_API static Path exePath();
	DRACO_COMMON_API static Path exeDir();
	DRACO_COMMON_API static Path homeDir();
	DRACO_COMMON_API static std::string nativeExePath();
	DRACO_COMMON_API static std::string nativeExeDir();
	DRACO_COMMON_API static std::string nativeHomeDir();

	DRACO_COMMON_API Path();
	DRACO_COMMON_API Path(const std::string &source);
	DRACO_COMMON_API Path(const std::string &source, size_t pos, size_t len = std::string::npos);
	DRACO_COMMON_API Path(const char *source);
	DRACO_COMMON_API Path(const char *source, size_t n);
	DRACO_COMMON_API Path(size_t n, char c);

	// the following constructor is deceptive when put into a shared library because the needed templates won't necessarily be provided (I think?)
	//template<class InputIterator>
	//DRACO_COMMON_API Path(InputIterator first, InputIterator last);
	
	DRACO_COMMON_API std::string native() const;
	DRACO_COMMON_API bool exists() const;
	DRACO_COMMON_API bool isDir() const;
	DRACO_COMMON_API std::vector<std::string> dirList(bool includeHidden = false) const;
	DRACO_COMMON_API std::string fileName() const;
    DRACO_COMMON_API Path super() const;
	DRACO_COMMON_API Path &clean();
	DRACO_COMMON_API Path &addSlash();
	DRACO_COMMON_API Path &cutSlash();
	DRACO_COMMON_API Path &expand();

/* UNIMPLEMENTED */	DRACO_COMMON_API std::string fileType() const;	/* UNIMPLEMENTED */

private:
	static Path _exePath;
	static Path _exeDir;
	static Path _homeDir;
	static std::string _nativeExePath;
	static std::string _nativeExeDir;
	static std::string _nativeHomeDir;

	static void initialize();
	static void updateNativeExePath();
	static void updateNativeHomeDir();

	void convert();

};


#endif // DRACO_FILE_SYSTEM_H
