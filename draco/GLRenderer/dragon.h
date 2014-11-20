#ifndef GL_DRAGON_OBJ_H
#define GL_DRAGON_OBJ_H

#include "camera.h"
#include "window.h"
#include "glRenderer.h"

class Controls;

class DragonEngine {
	private:
	   Camera * cam;
	   GameWindow * win;
	   GLRenderer * rend;
	   Controls * controls;
	public:
	   DragonEngine();
	   void initWindow(int w, int h);
	   void placeCamera(GLfloat c_x, GLfloat c_y, GLfloat c_z,	// location of the camera
						GLfloat v_x, GLfloat v_y, GLfloat v_z,	// look-at point
						GLfloat u_x, GLfloat u_y, GLfloat u_z	// up vector
						);
		void initRenderer();
		void render();
		void event(int keyCode);
		void motionEvent(int x, int y);
	   //GameWindow & getWindow();
};

#endif
