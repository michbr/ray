
#include "modelViewer.h"
#include "FL/Fl_File_Chooser.H"
#include "FL/Fl_Box.H"
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

#if !HAVE_GL
class cube_box : public Fl_Box {
public:
  double lasttime;
  int wire;
  double size;
  double speed;
  cube_box(int x,int y,int w,int h,const char *l=0)
    :Fl_Box(FL_DOWN_BOX,x,y,w,h,l){
      label("This demo does\nnot work without GL");
  }
};
#else


class cube_box : public Fl_Gl_Window {
  void draw();
  int handle(int);
public:
  double lasttime;
  int wire;
  double size;
  double speed;
  cube_box(int x,int y,int w,int h,const char *l=0)
    : Fl_Gl_Window(x,y,w,h,l) {lasttime = 0.0;}
};

float v0[3] = {0.0, 0.0, 0.0};
float v1[3] = {1.0, 0.0, 0.0};
float v2[3] = {1.0, 1.0, 0.0};
float v3[3] = {0.0, 1.0, 0.0};
float v4[3] = {0.0, 0.0, 1.0};
float v5[3] = {1.0, 0.0, 1.0};
float v6[3] = {1.0, 1.0, 1.0};
float v7[3] = {0.0, 1.0, 1.0};

#define v3f(x) glVertex3fv(x)

void drawcube(int wire) {
/* Draw a colored cube */
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

void cube_box::draw() {
  lasttime = lasttime+speed;
  if (!valid()) {
    glLoadIdentity();
    glViewport(0,0,w(),h());
    glEnable(GL_DEPTH_TEST);
    glFrustum(-1,1,-1,1,2,10000);
    glTranslatef(0,0,-10);
    gl_font(FL_HELVETICA_BOLD, 16 );
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(float(lasttime*1.6),0,0,1);
  glRotatef(float(lasttime*4.2),1,0,0);
  glRotatef(float(lasttime*2.3),0,1,0);
  glTranslatef(-1.0, 1.2f, -1.5);
  glScalef(float(size),float(size),float(size));
  drawcube(wire);
  glPopMatrix();
  gl_color(FL_GRAY);
  glDisable(GL_DEPTH_TEST);
  gl_draw(wire ? "Cube: wire" : "Cube: flat", -4.5f, -4.5f );
  glEnable(GL_DEPTH_TEST);
}

int cube_box::handle(int e) {
  switch (e) {
  case FL_ENTER: cursor(FL_CURSOR_CROSS); break;
  case FL_LEAVE: cursor(FL_CURSOR_DEFAULT); break;
  }
  return Fl_Gl_Window::handle(e);
}
#endif
cube_box *cube, *cube2;

void makeform(const char *name, Fl_Group * pane) {
  cube = new cube_box(23,10,344,344, 0);
  cube2 = new cube_box(375,10,344,344, 0);
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


SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new StartTab(type, pane, file);
}

SCALE_API const char *scaleName() {
	return START_TAB_NAME;
}


StartTab::StartTab(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	{
		Fl_File_Chooser *chooser = new Fl_File_Chooser(startDir.c_str(), "", Fl_File_Chooser::SINGLE, "DA FILES!!");
		chooser->ok_label("open");
  makeform("test", pane);
  static Fl_Menu_Item   items[] = {
    { "Print", 0, 0, 0, FL_SUBMENU },
    { "Print window", 0, print_cb, 0, 0 },
    { 0 },
    { 0 }
  };
  Fl_Sys_Menu_Bar *menubar_;
  menubar_ = new Fl_Sys_Menu_Bar(0, 0, 60, 20);
  menubar_->box(FL_FLAT_BOX);
  menubar_->menu(items);
   cube->wire = 0; cube2->wire = 1;
  char ** array = new char *[1];
  string test = "test";
  array[0] = new char[5];
  strcpy(array[0], test.c_str());
  cube->show();
  cube2->show();
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
  for (;;) {
    if (pane->visible())  //&& speed->value())
      {if (!Fl::check()) break;}    // returns immediately
    else
      {if (!Fl::wait()) break;} // waits until something happens
    cube->wire = true;//wire->value();
    cube2->wire = false;//!wire->value();
    cube->size = cube2->size = 1.0;//size->value();
    cube->speed = cube2->speed = 1.0;//speed->value();
    cube->redraw();
    cube2->redraw();
  }
	}
	
}
StartTab::~StartTab() {
	free(pane);
}


