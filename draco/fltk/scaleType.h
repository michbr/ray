
#pragma once

#include "scale.h"

#include <string>


class ScaleType {
public:
	ScaleType(const std::string &name, const std::string &libName);
	~ScaleType();

	const std::string &getFileName() const;
	const std::string &getName() const;

	Scale *construct();

private:
	std::string name;
	std::string libName;

	void *lib;
	void *constructor;
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
