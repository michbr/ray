#ifndef MODEL_VIEWER_TAB
#define MODEL_VIEWER_TAB

#include "scale.h"

#include "FL/Fl_Group.H"

#include <string>


// this works around a bug in MinGW
#ifdef __MINGW32__
	typedef _off64_t off64_t;
#endif

const char *START_TAB_NAME = "Model Viewer";

class ModelViewerTab: public Scale  {
public:
	ModelViewerTab(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	void draw();
	~ModelViewerTab();
};

#endif
