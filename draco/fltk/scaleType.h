
#pragma once

#define NAME_GETTER_NAME "scaleName";
#define CONSTRUCTOR_NAME "constructScale";
class ScaleType;

#include "scale.h"

#include <string>


typedef Scale *(*ScaleConstructor)(ScaleType *type);
typedef const char *(*ScaleNameGetter)();


class ScaleType {
public:
	std::string name;
	ScaleType(const std::string &name, const std::string &libName);
	~ScaleType();

	void load();
	void unload();
	bool loaded();
	void *loadFunction(const std::string &funcName) const;

	const std::string &getLibName() const;
	const char *getLibExtension() const;
	const char *getRealName() const;

	Scale *construct();

private:
	std::string libName;

	void *lib;
	ScaleConstructor scaleConstructor;
	ScaleNameGetter nameGetter;

	void *loadLibrary();
};



//#ifdef _WIN32
//
//#include <windows.h>
//
//class ScaleType {
//private:
//	HINSTANCE lib;
//
//};
//
//#elif defined __linux__
//
//#elif defined __APPLE__
//
//#endif
