
#ifndef DRACO_FILE_CHOOSER_H
#define DRACO_FILE_CHOOSER_H


#include "util/path.h"
#include "FL/Fl_Multi_Browser.H"

#include <string>


class DirectoryViewer: public Fl_Multi_Browser {
public:
	DirectoryViewer(int x, int y, int w, int h, std::string path, const char *label=NULL);

	void showHidden(bool show=false);
	bool showHidden() const;
	void setDir(std::string path);
	
protected:
	bool _showHidden;
	Path path;
	
};


#endif // DRACO_FILE_CHOOSER_H
