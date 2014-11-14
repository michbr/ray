#ifndef GL_CONTROL_OBJ_H
#define GL_CONTROL_OBJ_H

#include "camera.h"
#include <GL/gl.h>

class DragonEngine;

class Controls {
	private:
	   DragonEngine * engine;
	   Camera<GLfloat> * cam;
	   int mouse_x, mouse_y;
	public:
	   Controls(DragonEngine & eng, Camera<GLfloat> &);
	   void keyPress(int keyCode);
	   void motionEvent(int x, int y);
	   
	
};

#endif