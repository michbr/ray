
#pragma once


#include "scale.h"
#include "glPane.h"

#include "FL/Fl_Group.H"

#include <string>


// this works around a bug in MinGW
#ifdef __MINGW32__
	typedef _off64_t off64_t;
#endif

const char *START_TAB_NAME = "Start";


class StartTab: public Scale, public GLDrawable {
public:
	StartTab(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	void draw();
	~StartTab();

private:
	double lasttime;
	double speed;
	double size;
	int wire;
};
