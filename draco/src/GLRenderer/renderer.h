#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include "window.h"
#include "camera.h"
#include <GL/gl.h>

class Renderer {
	private:
	  // GameWindow & window;
	   //static bool initialized;
	   //static Renderer & instance;
	   Camera<GLfloat> * cam;
	   
	   void initGL(GameWindow & win);
	   void initialize(GameWindow & win);
	public:
	   Renderer(GameWindow & win, Camera<GLfloat> * cam);
	   
	   //static Renderer & getInstance();
	   void render();
	   Camera<GLfloat> & getCam();
};

#endif