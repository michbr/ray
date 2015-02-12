#ifndef GLRENDERER_TAB_OBJ
#define GLRENDERER_TAB_OBJ

#include "scale.h"
#include "dragon.h"
#include "glPane.h"
#include "thread.h"

#include "FL/Fl_Group.H"

#include <string>


// this works around a bug in MinGW
#ifdef __MINGW32__
        typedef _off64_t off64_t;
#endif

const char *START_TAB_NAME = "GLRenderer";

class GLTab: public Scale, public Runnable, public GLDrawable  {
private:
	DragonEngine engine;
	Thread * main;
	cube_box * display;
public:
        GLTab(ScaleType *type, Fl_Group *pane, const std::string &startDir);
        void draw();
	void initialize();
	void run();
	static void update(void * context);
        ~GLTab();
};

#endif
