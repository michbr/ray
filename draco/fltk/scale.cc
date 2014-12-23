
#include "scale.h"


using namespace std;



Scale::Scale(ScaleType *type, Fl_Group *pane, const string &file): type(type), pane(pane), file(file) {}


const string &Scale::getLibName() const {
	return type->getLibName();
}
const string &Scale::getFileName() const {
	return file;
}
const string &Scale::getName() const {
	return type->name;
}
