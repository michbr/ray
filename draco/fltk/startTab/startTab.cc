
#include "startTab.h"
#include "directoryViewer.h"
#include "FL/Fl_File_Chooser.H"
#include "FL/Fl_Box.H"

#include <string>
#include <iostream>


using namespace std;


SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new StartTab(type, pane, file);
}

SCALE_API const char *scaleName() {
	return START_TAB_NAME;
}


StartTab::StartTab(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	{
		DirectoryViewer *viewer = new DirectoryViewer(pane->x() +4, pane->y() +4, pane->w() -8, pane->h() -35, startDir, "");
		pane->resizable(viewer);
		Fl_Button *openBut = new Fl_Button(pane->x() +pane->w() -84, pane->y() +pane->h() -29, 80, 25, "Open");
	}
	
}
StartTab::~StartTab() {
	free(pane);
}


