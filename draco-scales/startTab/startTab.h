
#pragma once

#include "scale.h"
#include "FL/Fl_Group.H"

#include <string>

#ifdef __MINGW32__
	typedef _off64_t off64_t;
#endif

const char *START_TAB_NAME = "Start";


class StartTab: public Scale {
public:
	StartTab(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	~StartTab();

private:

};

