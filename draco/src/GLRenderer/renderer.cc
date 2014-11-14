#include "renderer.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

using namespace std;

GLfloat		vertices[] =
  {
   
     1, 1, 1,    1, -1,  1,    1,  -1,  -1,    1,  1, -1,
-1, 1, 1,   -1, 1,  -1,   -1,  -1,  -1,   -1,  -1, 1,
    1, -1, 1,   -1, -1,  1,    -1, -1,  -1,    1, -1, -1,
    -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
    -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
    1, 1,  1,   -1,  1,  1,    -1,  -1,  1,    1, -1,  1
  };

GLfloat		colors[] =
  {
    1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,
    0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,
    0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,
    1, 1, 0,   1, 1, 0,   1, 1, 0,   1, 1, 0,
    1, 0, 1,   1, 0, 1,   1, 0, 1,   1, 0, 1, //changing this from 1, 0, 1 to green
    0, 1, 1,   0, 1, 1,   0, 1, 1,   0, 1, 1
  };

Renderer::Renderer(GameWindow & win, Camera<GLfloat> * camera) {
	
	cam = camera;
	//cout << *camera << endl;
	//cout << *cam << endl;
	initialize(win);
	//window = win;	
}

void Renderer::initialize(GameWindow & win) {
	//instance = Renderer(win);
	initGL(win);
	//return *cam;
}

void Renderer::initGL(GameWindow & win) {
	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	//cam = new Camera<GLfloat>(0., 0., 1.5, 0., 0, 1., 0., 1., 0.);
	//cam.drawCube();'
	//cout << "gotcha?" << *cam << endl;
	//cout << *cam << endl;
	cam->setPerspective(60, (GLfloat)win.getWidth()/(GLfloat)win.getHeight(), .01, 999);
	//gluPerspective(60, (GLfloat)win.getWidth()/(GLfloat)win.getHeight(), .01, 999);
	//cam->Look();

	//TODO
	glViewport(0, 0, win.getWidth(), win.getHeight());

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();


	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//cam->Look();
	
	GLenum error = glGetError();
	
	if (error) {
		cerr << "OpenGL error: " << error << endl;
	}
}

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//cam->setPerspective(60, 1, .01, 999);
	
	cam->Look();//At(0, 0, 0);
	//gluLookAt(cam_x, cam_y, cam_z, vrp_x, vrp_y, vrp_z, up_x, up_y, up_z);
	//glTranslatef(cam_x, cam_y, cam_z);
	//glRotatef(30, 1, 0, 0);
	//glRotatef(alpha, 0, 1, 0);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 24);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	//Update screen
	//glutSwapBuffers();
}