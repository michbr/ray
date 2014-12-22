
#include "scaleManager.h"


using namespace std;


ScaleType::ScaleType(const string &name, const string &libName): lib(NULL) {
	this->name = name;
	this->libName = libName;
}

bool ScaleType::loaded() {
	return lib != NULL;
}

ScaleType::~ScaleType() {
	unload();
}

Scale *ScaleType::construct() {
	return scaleConstructor(this);
}

const string &ScaleType::getLibName() const {
	return libName;
}
const char *ScaleType::getRealName() const {
	return nameGetter();
}

void ScaleType::load() {
	unload();
	lib = loadLibrary();

	if (!lib)
		throw string("Could not load shared library ") + libName + getLibExtension();

	nameGetter = (ScaleNameGetter)loadFunction(NAME_GETTER_NAME);
	if (nameGetter == NULL) {
		unload();
		throw string("Could not load shared library function ") + libName + getLibExtension() + ": " + NAME_GETTER_NAME;
	}

	scaleConstructor = (ScaleConstructor)loadFunction(CONSTRUCTOR_NAME);
	if (scaleConstructor == NULL) {
		unload();
		throw string("Could not load shared library function ") + libName + getLibExtension() + ": " + CONSTRUCTOR_NAME;
	}
}
