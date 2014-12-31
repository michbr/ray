
#ifndef DRACO_FILE_SYSTEM_H
#define DRACO_FILE_SYSTEM_H

#include <list>
#include <string>


#define MAX_EXECUTABLE_PATH_LENGTH 512


class Path: public std::string {
public:
	static Path exePath();
	static Path exeDir();
	static std::string nativeExePath();
	static std::string nativeExeDir();

	Path();
	Path(const std::string &source);
	Path(const std::string &source, size_t pos, size_t len = std::string::npos);
	Path(const char *source);
	Path(const char *source, size_t n);
	Path(size_t n, char c);
	template<class InputIterator>
	Path(InputIterator first, InputIterator last);
	
	std::string native() const;
	
	std::list<std::string> dirList() const;
	std::string fileType() const;

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
