#include "modelViewer.h"
#include "common/glPane.h"
#include "common/thread.h"

#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Light_Button.H>
#include <FL/Fl_Slider.H>

#include <cstring>
#include <string>
#include <iostream>


using namespace std;

#if HAVE_GL

#define v3f(x) glVertex3fv(x)

float v0[3] = {0.0, 0.0, 0.0};
float v1[3] = {1.0, 0.0, 0.0};
float v2[3] = {1.0, 1.0, 0.0};
float v3[3] = {0.0, 1.0, 0.0};
float v4[3] = {0.0, 0.0, 1.0};
float v5[3] = {1.0, 0.0, 1.0};
float v6[3] = {1.0, 1.0, 1.0};
float v7[3] = {0.0, 1.0, 1.0};

class Cube : public GLDrawable {
private:
	int wire;
	double lasttime;
	double size;
	double speed;	

	void drawCube() {
		// Draw a colored cube
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(0,0,255);
		v3f(v0); v3f(v1); v3f(v2); v3f(v3);
		glEnd();
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(0,255,255); v3f(v4); v3f(v5); v3f(v6); v3f(v7);
		glEnd();
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(255,0,255); v3f(v0); v3f(v1); v3f(v5); v3f(v4);
		glEnd();
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(255,255,0); v3f(v2); v3f(v3); v3f(v7); v3f(v6);
		glEnd();
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(0,255,0); v3f(v0); v3f(v4); v3f(v7); v3f(v3);
		glEnd();
		glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
		glColor3ub(255,0,0); v3f(v1); v3f(v2); v3f(v6); v3f(v5);
		glEnd();
	}
public:
	Cube (int w) {
		wire = w;
		lasttime = 0.0;
		size = 1.0;
		speed = 1.0;
	}
	void initialize() {
              glLoadIdentity();
              glViewport(0,0,344,344);
              glEnable(GL_DEPTH_TEST);
              glFrustum(-1,1,-1,1,2,10000);
              glTranslatef(0,0,-10);
              gl_font(FL_HELVETICA_BOLD, 16 );
	
	}
	void draw() {
		lasttime = lasttime+speed;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glRotatef(float(lasttime*1.6),0,0,1);
		glRotatef(float(lasttime*4.2),1,0,0);
		glRotatef(float(lasttime*2.3),0,1,0);
		glTranslatef(-1.0, 1.2f, -1.5);
		glScalef(float(size),float(size),float(size));
		drawCube();
		glPopMatrix();
		gl_color(FL_GRAY);
		glDisable(GL_DEPTH_TEST);
		gl_draw(wire ? "Cube: wire" : "Cube: flat", -4.5f, -4.5f );
		glEnable(GL_DEPTH_TEST);
	}
	void handleEvent(int key) {

	}
};

#endif

GLPane *cube, *cube2;

class DisplayUpdater : public Runnable {
public:
	void run() {
		while (true) {
			this_thread::sleep_for(chrono::milliseconds(100));
			Fl::awake((Fl_Awake_Handler)update, this);
		}
	}
	static void update(void * context) {
		cube->redraw();
		cube2->redraw();
	}
};

void makeform(Fl_Group * pane) {

  Fl_Box *b = new Fl_Box(FL_NO_BOX,cube->x(),90,
             cube->w(),220,0);
  pane->resizable(b);
  b->hide();
}

// added to demo printing
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Printer.H>

void print_cb(Fl_Widget *w, void *data)
{
  Fl_Printer printer;
  Fl_Window *win = Fl::first_window();
  if(!win) return;
  if( printer.start_job(1) ) return;
  if( printer.start_page() ) return;
  printer.scale(0.5,0.5);
  printer.print_widget( win );
  printer.end_page();
  printer.end_job();
}


DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new ModelViewerTab(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
	return START_TAB_NAME;
}

Thread * updater;
ModelViewerTab::ModelViewerTab(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	{
		Fl_File_Chooser *chooser = new Fl_File_Chooser(startDir.c_str(), "", Fl_File_Chooser::SINGLE, "DA FILES!!");
		chooser->ok_label("open");
		Cube * c1 = new Cube(0);
		Cube * c2 = new Cube(1);
		cube = new GLPane(c1, 23,50,344,344, 0);
		cube2 = new GLPane(c2, 375,50,344,344, 0);
		makeform(pane);

//		cube->show();
//		cube2->show();
		#if 0
		  // This demonstrates how to manipulate OpenGL contexts.
		  // In this case the same context is used by multiple windows (I'm not
		  // sure if this is allowed on Win32, can somebody check?).
		  // This fixes a bug on the XFree86 3.0 OpenGL where only one context
		  // per program seems to work, but there are probably better uses for
		  // this!
		  cube->make_current(); // causes context to be created
		  cube2->context(cube->context()); // share the contexts
		#endif
		if (pane->visible()) {
			updater = new Thread(new DisplayUpdater());
			updater->start();
		}
	}
}

ModelViewerTab::~ModelViewerTab() {
	free(pane);
}
