

#include "../directoryViewer.h"

using namespace std;


void addressChange(Fl_Widget *, void *dv) {
	DirectoryViewer *dirViewer = (DirectoryViewer *) dv;
	dirViewer->update();
}


DirectoryViewer::DirectoryViewer(int x, int y, int w, int h, string path, const char *label):
	Fl_Group(x, y, w, h, label), _showHidden(false) {
//	upBut = new Fl_Button();
	addressBar = new Fl_File_Input(x, y, w, 40, path.c_str());
	browser = new Fl_Multi_Browser(x, y +42, w, h -42, "");
	addressBar->callback(addressChange, this);
//	add(upBut);
	add(addressBar);
	add(browser);
	resizable(browser);
	setDir(path);
}
DirectoryViewer::~DirectoryViewer() {
}

void DirectoryViewer::showHidden(bool show) {
	_showHidden = show;
    update();
}
bool DirectoryViewer::showHidden() const {
	return _showHidden;
}

void DirectoryViewer::setDir(string path) {
    addressBar->value(path.c_str());
    update();
}

void DirectoryViewer::update() {
	path = addressBar->value();
	if (path.exists()) {
		if (path.isDir())
			directory = path;
		else
            directory = path.super();
		list<string> fileList = directory.dirList(_showHidden);

		browser->clear();
		for(string file: fileList)
			browser->add(file.c_str());
    }
}
