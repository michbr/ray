

#include "directoryViewer.h"

using namespace std;


DirectoryViewer::DirectoryViewer(int x, int y, int w, int h, string path, const char *label):
	Fl_Multi_Browser(x, y, w, h, label), _showHidden(false), path(path) {
	
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


