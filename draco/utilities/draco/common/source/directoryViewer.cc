

#include "../directoryViewer.h"

#include <ctime>
#include <iostream>


using namespace std;


double DirectoryViewer::DOUBLE_CLICK_TIME = 0.5;


//////////////////
//  UI Actions  //
//////////////////
void addressChange(Fl_Widget *t, void *dv) {
	((DirectoryViewer *) dv)->update();
}

void browserChange(Fl_Widget *t, void *dv) {
	DirectoryViewer &dirViewer = *(DirectoryViewer*)dv;
	Fl_Multi_Browser &browser = *(Fl_Multi_Browser*)t;
	time_t now = clock();
	string selected = browser.text(browser.value());
	Path newPath = (string)dirViewer.directory.addSlash() +selected;
	if (Fl::event() == FL_KEYDOWN
		|| (now < dirViewer.lastSelection +(DirectoryViewer::DOUBLE_CLICK_TIME *CLOCKS_PER_SEC)
		&& selected == dirViewer.lastSelected)) {
		dirViewer.setPath(newPath);
	} else {
		dirViewer.addressBar->value(newPath.c_str());
		dirViewer.lastSelection = now;
		dirViewer.lastSelected = selected;
	}
}

void goHome(Fl_Widget *t, void *dv) {
	DirectoryViewer &dirViewer = *(DirectoryViewer*)dv;
	dirViewer.setPath(Path::nativeHomeDir());
}


DirectoryViewer::DirectoryViewer(int x, int y, int w, int h, string path, const char *label):
	Fl_Group(x, y, w, h, label), _showHidden(false) {
	Fl_Group *bar = new Fl_Group(x, y, w, 40);
	homeBut = new Fl_Button(x +2, y +10, 45, 30, "Home");
	addressBar = new Fl_File_Input(x +49, y, w -49, 40);
	current(this);
	browser = new Fl_Multi_Browser(x, y +42, w, h -42);
	homeBut->callback(goHome, this);
	addressBar->callback(addressChange, this);
	browser->callback(browserChange, this);
//	bar->add(homeBut);
//	bar->add(addressBar);
////	add(homeBut);
//	add(addressBar);
//	add(browser);
	bar->resizable(addressBar);
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
	lastSelection = 0;
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

std::string DirectoryViewer::value() const {
	return string(addressBar->value());
}
