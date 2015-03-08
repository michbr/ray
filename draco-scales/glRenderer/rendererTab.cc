#include "rendererTab.h"

#include <FL/Fl.H>

using namespace std;

DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
        return new GLTab(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
        return START_TAB_NAME;
}


GLTab::GLTab(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
        pane->current(pane);
	main = new Thread(this);
        {
		display = new cube_box(this, 5, 30, 500, 500, 0);
//                  cube->make_current(); // causes context to be created
  //                cube2->context(cube->context()); // share the contexts


	        engine.initWindow(500, 500);
        	engine.placeCamera (
                    0, 0, 8.,
                    0, 0, 0,
                    0., 1., 0.
            );
       // display->show();
        main->start();
        }

}

void GLTab::run() {
	while(true) {
       this_thread::sleep_for(chrono::milliseconds(1000));
        Fl::awake((Fl_Awake_Handler)update, this);
	}
}

void GLTab::initialize() {
	engine.initRenderer();
}

void GLTab::draw() {
	engine.render();
}

GLTab::~GLTab() {
        free(pane);
}

void GLTab::update(void * context) {
	GLTab * instance = (GLTab *) context;
	instance->display->redraw();
}
