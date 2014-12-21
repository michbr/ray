
#include "startTab.h"

#include <string>

using namespace std;



StartTab::StartTab(const string &name, const string &fileName) {
	this->name = name;
	this->fileName = fileName;
}


StartTab::~StartTab() {
}


const string &StartTab::getFileName() const {
	return fileName;
}
const string &StartTab::getName() const {
	return name;
}
