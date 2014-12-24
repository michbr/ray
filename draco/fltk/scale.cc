
#include "scale.h"


using namespace std;


const string &Scale::getLibName() const {
	return type->getLibName();
}
const string &Scale::getFileName() const {
	return file;
}
const string &Scale::getName() const {
	return type->name;
}
