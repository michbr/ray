
#ifndef DRACO_FILE_CHOOSER_H
#define DRACO_FILE_CHOOSER_H


#include "util/path.h"
#include "FL/Fl_Multi_Browser.H"
#include "FL/Fl_File_Input.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Group.H"

#include <string>


class DirectoryViewer: public Fl_Group {
public:
	DirectoryViewer(int x, int y, int w, int h, std::string path, const char *label=NULL);
	~DirectoryViewer();

	void showHidden(bool show);
	bool showHidden() const;
	void setDir(std::string path);
	
protected:
	bool _showHidden;
	Path path;
	Fl_Button *upBut;
	Fl_File_Input *addressBar;
	Fl_Multi_Browser *browser;

};


#endif // DRACO_FILE_CHOOSER_H
