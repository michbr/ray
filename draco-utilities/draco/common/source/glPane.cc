
#include "glPane.h"

#include <FL/Fl_Box.H>
#include <FL/gl.h>


cube_box::cube_box(GLDrawable * toDraw,  int x,int y,int w,int h,const char *l)
: Fl_Gl_Window(x,y,w,h,l) {
	drawable = toDraw;
}

void cube_box::draw() {
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

int cube_box::handle(int e) {
	switch (e) {
		case FL_ENTER: cursor(FL_CURSOR_CROSS); break;
		case FL_LEAVE: cursor(FL_CURSOR_DEFAULT); break;
	}
	return Fl_Gl_Window::handle(e);
}
