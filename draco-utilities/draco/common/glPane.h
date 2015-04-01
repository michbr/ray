#ifndef GL_PANE_WIDGET
#define GL_PANE_WIDGET

#include "EXPORT.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Gl_Window.H>

class GLDrawable { 
public:
	DRACO_COMMON_API virtual void draw() = 0;
	DRACO_COMMON_API virtual void initialize() = 0;
	DRACO_COMMON_API virtual void handleEvent(int key) = 0;
}; 


#if !HAVE_GL
class GLPane : public Fl_Box {

public:
  DRACO_COMMON_API GLPane(int x,int y,int w,int h,const char *l=0)
    :Fl_Box(FL_DOWN_BOX,x,y,w,h,l){
      label("This demo does\nnot work without GL");
  }
};
#else


class GLPane : public Fl_Gl_Window {
private:
  GLDrawable * drawable;

  void draw();
  int handle(int);
public:
	DRACO_COMMON_API GLPane(GLDrawable *toDraw, int x, int y, int w, int h, const char *l=0);
};
#endif

#endif

