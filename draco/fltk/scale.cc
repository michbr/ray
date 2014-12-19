
#include "scale.h"


using namespace std;



Scale::Scale(const string &name, const string &fileName) {
	this->name = name;
	this->fileName = fileName;
}


Scale::~Scale() {
}


const string &Scale::getFileName() const {
	return fileName;
}
const string &Scale::getName() const {
	return name;
}
