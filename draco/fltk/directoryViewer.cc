

#include "directoryViewer.h"

using namespace std;


DirectoryViewer::DirectoryViewer(int x, int y, int w, int h, string path, const char *label):
	Fl_Group(x, y, w, h, label), _showHidden(false), path(path) {
//	upBut = new Fl_Button();
	addressBar = new Fl_File_Input(x, y, w, 40, path.c_str());
	browser = new Fl_Multi_Browser(x, y +42, w, h -42, "");
//	add(upBut);
	add(addressBar);
	add(browser);
	resizable(browser);
}
DirectoryViewer::~DirectoryViewer() {
}

void DirectoryViewer::showHidden(bool show) {
	_showHidden = show;
}
bool DirectoryViewer::showHidden() const {
	return _showHidden;
}

void DirectoryViewer::setDir(string path) {
	this->path = path;
}


