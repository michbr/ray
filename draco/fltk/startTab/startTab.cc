
#include "startTab.h"
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
		Fl_Box *box = new Fl_Box(20, 40, 360, 100, "Hello, World! This is a new tab.");
		box->box(FL_DOWN_FRAME);
		box->labelsize(24);
		box->labelfont(FL_BOLD + FL_ITALIC);
		box->labeltype(FL_SHADOW_LABEL);
	}
	
}
StartTab::~StartTab() {
	free(pane);
}


