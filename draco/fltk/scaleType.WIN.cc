
#ifdef _WIN32


#include "scaleType.h"

#include <windows.h>
#include <iostream>


const char *LIB_EXTENSION = ".dll";


using namespace std;


void ScaleType::unload() {
	if (lib == NULL) return;
	FreeLibrary((HMODULE)lib);
	lib = NULL;
}

void *ScaleType::loadLibrary() {
	cout << libName << endl;
	return LoadLibrary((string("../scales/") + libName + LIB_EXTENSION).c_str());
}

void *ScaleType::loadFunction(const std::string &funcName) const {
	return GetProcAddress((HMODULE)lib, funcName.c_str());
}

const char *ScaleType::getLibExtension() const {
	return LIB_EXTENSION;
}


#endif // _WIN32
