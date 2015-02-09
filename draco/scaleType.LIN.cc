
#ifdef __linux__


#include "scaleManager.h"
#include "draco.h"
#include "common/path.h"

#include <dlfcn.h>
#include <iostream>


const char *LIB_EXTENSION = ".so";


using namespace std;


void ScaleType::unload() {
	if (lib == NULL) return;
	dlclose(lib);
	lib = NULL;
}

void *ScaleType::loadLibrary() {
	cout << (Path::exeDir() +ROOT_PATH +SCALE_DIR +libName +LIB_EXTENSION) << endl;
	return dlopen((Path::exeDir() +ROOT_PATH +SCALE_DIR +libName +LIB_EXTENSION).c_str(), RTLD_LAZY);
}

void *ScaleType::loadFunction(const std::string &funcName) const {
	void *func = dlsym(lib, funcName.c_str());
	if (func == NULL) cerr << dlerror() << endl;
	return func;
}

const char *ScaleType::getLibExtension() const {
	return LIB_EXTENSION;
}


#endif // __linux__
