
#ifdef _WIN32


#include "scaleType.h"

#include <windows.h>
#include <iostream>


using namespace std;


ScaleType::ScaleType(const string &name, const string &libName) {
	this->name = name;
	this->libName = libName;
	lib = LoadLibrary(libName.c_str());

	if (!lib)
		throw string("Could not load DLL ") +libName;

	int(__stdcall *func)();
	string funcName = "getName";
	func = GetProcAddress((HMODULE)lib, funcName.c_str());
	if (!func)
		throw string("Could not load DLL function ") + libName + ": " + funcName;


}

ScaleType::~ScaleType() {
	FreeLibrary((HMODULE)lib);
}

Scale *ScaleType::construct() {
	return new Scale(name, libName);
}


#endif // _WIN32