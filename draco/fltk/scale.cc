
#include "scale.h"


using namespace std;



Scale::Scale(ScaleType *type): type(type) {}


Scale::~Scale() {
}


const string &Scale::getFileName() const {
	return type->getLibName();
}
const string &Scale::getName() const {
	return type->name;
}
