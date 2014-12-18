
#ifdef _WIN32

#include "scale.h"

#include <windows.h>
#include <iostream>


using namespace std;


Scale *Scale::load(const string &fileName) {
	HINSTANCE lib = LoadLibrary(fileName.c_str());

	if (!lib) {
		cerr << "Could not load DLL " << fileName << endl;
		exit(1);
	}

	int(__stdcall *func)();
	string name = "getName";
	func = GetProcAddress(lib, name.c_str());
	if (!func) {
		cerr << "Could not load DLL function " << fileName << ": " << name << endl;
		exit(1);
	}


}


#endif // _WIN32