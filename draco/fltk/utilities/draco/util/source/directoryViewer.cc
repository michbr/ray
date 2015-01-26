

#include "../directoryViewer.h"

#include <ctime>
#include <iostream>


using namespace std;


double DirectoryViewer::DOUBLE_CLICK_TIME = 0.5;


void addressChange(Fl_Widget *t, void *dv) {
	((DirectoryViewer *) dv)->update();
}

void browserChange(Fl_Widget *t, void *dv) {
	DirectoryViewer &dirViewer = *(DirectoryViewer*)dv;
	Fl_Multi_Browser &browser = *(Fl_Multi_Browser*)t;
	time_t now = clock();
	string selected = browser.text(browser.value());
	Path newPath = (string)dirViewer.directory.addSlash() +selected;
	if (now < dirViewer.lastSelection +(DirectoryViewer::DOUBLE_CLICK_TIME *CLOCKS_PER_SEC)
		&& selected == dirViewer.lastSelected) {
		dirViewer.setPath(newPath);
	} else {
		dirViewer.addressBar->value(newPath.c_str());
	}
	dirViewer.lastSelection = now;
	dirViewer.lastSelected = selected;
}


DirectoryViewer::DirectoryViewer(int x, int y, int w, int h, string path, const char *label):
	Fl_Group(x, y, w, h, label), _showHidden(false) {
//	upBut = new Fl_Button();
	addressBar = new Fl_File_Input(x, y, w, 40, path.c_str());
	browser = new Fl_Multi_Browser(x, y +42, w, h -42, "");
	addressBar->callback(addressChange, this);
	browser->callback(browserChange, this);
//	add(upBut);
	add(addressBar);
	add(browser);
	resizable(browser);
	setPath(path);
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

void DirectoryViewer::setPath(string path) {
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
