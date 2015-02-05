
#include "../path.h"

#include <iostream>

using namespace std;


Path Path::_exePath;
Path Path::_exeDir;
Path Path::_homeDir;
std::string Path::_nativeExePath;
std::string Path::_nativeExeDir;
std::string Path::_nativeHomeDir;

Path Path::exePath() {
	initialize();
    return _exePath;
}
Path Path::exeDir() {
	initialize();
    return _exeDir;
}
string Path::nativeExePath() {
	initialize();
    return _nativeExePath;
}
string Path::nativeExeDir() {
	initialize();
    return _nativeExeDir;
}
Path Path::homeDir() {
	initialize();
	return _homeDir;
}
string Path::nativeHomeDir() {
	initialize();
	return _nativeHomeDir;
}

void Path::initialize() {
	if (!_exePath.empty() && !_exeDir.empty())
		return;

	updateNativeExePath();
	_exePath = Path(_nativeExePath);
	_exeDir = _exePath.super();
	_nativeExeDir = _exeDir.native();

	updateNativeHomeDir();
	_homeDir = _nativeHomeDir;
}

Path::Path() {}
Path::Path(const string &source): string(source) {
	clean();
}
Path::Path(const string &source, size_t pos, size_t len): string(source, pos, len) {
	clean();
}
Path::Path(const char *source): string(source) {
	clean();
}
Path::Path(const char *source, size_t n): string(source, n) {
	clean();
}
Path::Path(size_t n, char c): string(n, c) {
	clean();
}
//template<class InputIterator>
//Path::Path(InputIterator first, InputIterator last): string(first, last) {
//	clean();
//}


Path Path::super() const {
	if (size() < 2)
		return *this;
	size_t pos = find_last_of('/', size() -2);
	if (pos == string::npos)
		return *this;
    return substr(0, pos +1);
}

Path &Path::clean() {
	convert();
	for (size_t pos = find("//"); pos != string::npos; pos = find("//")) {
		replace(pos, 2, "/");
	}
	return *this;
}

Path &Path::addSlash() {
	if (back() != '/')
		push_back('/');
	return *this;
}

Path &Path::cutSlash() {
	if (back() == '/')
		pop_back();
	return *this;
}

std::string Path::fileName() const {
	size_t length = (back() == '/')? size() -1: size();
	size_t pos = find_last_of('/', length);
	if (pos == string::npos)
		throw string("Invalid file path for fileName() call");
	++pos;
	length -= pos;
	return substr(pos, length);
}
