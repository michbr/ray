
#ifndef DRACO_FILE_CHOOSER_H
#define DRACO_FILE_CHOOSER_H


#include "EXPORT.h"
#include "path.h"
#include "FL/Fl_Multi_Browser.H"
#include "FL/Fl_File_Input.H"
#include "FL/Fl_Button.H"
#include "FL/Fl_Group.H"

#include <string>


class DirectoryViewer : public Fl_Group{
public:
	DRACO_UTIL_API DirectoryViewer(int x, int y, int w, int h, std::string path, const char *label = NULL);
	DRACO_UTIL_API ~DirectoryViewer();

	DRACO_UTIL_API void showHidden(bool show);
	DRACO_UTIL_API bool showHidden() const;
	DRACO_UTIL_API void setDir(std::string path);
	
protected:
	bool _showHidden;
	Path path;
	Fl_Button *upBut;
	Fl_File_Input *addressBar;
	Fl_Multi_Browser *browser;

};


#endif // DRACO_FILE_CHOOSER_H
