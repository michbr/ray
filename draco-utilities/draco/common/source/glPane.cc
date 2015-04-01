
#include "glPane.h"

#include <FL/Fl.H>


GLPane::GLPane(GLDrawable * toDraw,  int x,int y,int w,int h,const char *l)
: Fl_Gl_Window(x,y,w,h,l) {
	drawable = toDraw;
}

void GLPane::draw() {
	if (!valid()) {
		drawable->initialize();
//		glLoadIdentity();
//		glViewport(0,0,w(),h());
//		glEnable(GL_DEPTH_TEST);
//		glFrustum(-1,1,-1,1,2,10000);
//		glTranslatef(0,0,-10);
//		gl_font(FL_HELVETICA_BOLD, 16 );
	}
	drawable->draw();
}

int GLPane::handle(int e) {
	switch (e) {
		case FL_KEYDOWN: drawable->handleEvent(Fl::event_key());
		case FL_KEYUP:  drawable->handleEvent(Fl::event_key());
		case FL_ENTER: cursor(FL_CURSOR_CROSS); break;
		case FL_LEAVE: cursor(FL_CURSOR_DEFAULT); break;
	}
	return Fl_Gl_Window::handle(e);
}
