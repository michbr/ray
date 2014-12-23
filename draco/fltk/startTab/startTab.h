
#pragma once

#include "scale.h"
#include "FL/Fl_Group.H"

#include <string>


const char *START_TAB_NAME = "Start";


class StartTab: public Scale {
public:
	StartTab(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	~StartTab();

private:

};

