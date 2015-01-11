
#include "../path.h"

using namespace std;


Path Path::_exePath;
Path Path::_exeDir;
std::string Path::_nativeExePath;
std::string Path::_nativeExeDir;

Path Path::exePath() {
    updateExePaths();
    return _exePath;
}
Path Path::exeDir() {
    updateExePaths();
    return _exeDir;
}
string Path::nativeExePath() {
    updateExePaths();
    return _nativeExePath;
}
string Path::nativeExeDir() {
    updateExePaths();
    return _nativeExeDir;
}


Path::Path() {}
Path::Path(const string &source): string(source) {
	convert();
}
Path::Path(const string &source, size_t pos, size_t len): string(source, pos, len) {
	convert();
}
Path::Path(const char *source): string(source) {
	convert();
}
Path::Path(const char *source, size_t n): string(source, n) {
	convert();
}
Path::Path(size_t n, char c): string(n, c) {
	convert();
}
template<class InputIterator>
Path::Path(InputIterator first, InputIterator last): string(first, last) {
	convert();
}


void Path::updateExePaths() {
	if (!_exePath.empty() && !_exeDir.empty())
		return;

	updateNativeExePath();
	_exePath = Path(_nativeExePath);
	_exeDir = _exePath.substr(0, _exePath.find_last_of('/') +1);
	_nativeExeDir = _exeDir.native();
}


