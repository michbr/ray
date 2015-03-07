#include "glRenderer.h"
//#include "loadShader.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <GL/glext.h>

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

GLRenderer::GLRenderer(GameWindow & win, Camera * camera) {
	
	cam = camera;
	//cout << *camera << endl;
	//cout << *cam << endl;
	initialize(win);
	//window = win;	
}

void GLRenderer::initialize(GameWindow & win) {
	//instance = GLRenderer(win);
	initGL(win);
	//return *cam;
}

/*float cube[8][3] = {
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0, 
	1.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	0.0, 1.0, 1.0};*/

GLfloat cube[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

// This will identify our vertex buffer
GLuint vertexbuffer;

void GLRenderer::initGL(GameWindow & win) {
	glLoadIdentity();
	glViewport(0,0,win.getWidth(),win.getHeight());
	glEnable(GL_DEPTH_TEST);
	glFrustum(-1,1,-1,1,2,10000);
	glTranslatef(0,0,-10);
//	gl_font(FL_HELVETICA_BOLD, 16 );


 
// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);
 
// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
 
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
}

int                wire = 0;
double                lasttime = 0.0;
double                size = 1.0;
double                speed = 1.0;

#define v3f(x) glVertex3fv(x)

float v0[3] = {0.0, 0.0, 0.0};
float v1[3] = {1.0, 0.0, 0.0};
float v2[3] = {1.0, 1.0, 0.0};
float v3[3] = {0.0, 1.0, 0.0};
float v4[3] = {0.0, 0.0, 1.0};
float v5[3] = {1.0, 0.0, 1.0};
float v6[3] = {1.0, 1.0, 1.0};
float v7[3] = {0.0, 1.0, 1.0};



void drawCube() {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
	   (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);

	// Draw a colored cube 
/*	glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
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
	glEnd();*/
}


void GLRenderer::render() {
//	lasttime = lasttime+speed;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
//	glRotatef(float(lasttime*1.6),0,0,1);
//	glRotatef(float(lasttime*4.2),1,0,0);
//	glRotatef(float(lasttime*2.3),0,1,0);
//	glTranslatef(-1.0, 1.2f, -1.5);
//	glScalef(float(size),float(size),float(size));
	drawCube();
	glPopMatrix();
	glColor3f(.5, .5, .5);
/*	glDisable(GL_DEPTH_TEST);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
 
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	 
	glDisableVertexAttribArray(0);*/
	//gl_draw(wire ? "Cube: wire" : "Cube: flat", -4.5f, -4.5f );
//	glEnable(GL_DEPTH_TEST);

}
