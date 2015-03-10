#include "glRenderer.h"
#include "loadShader.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <GL/glext.h>

#include <iostream>
#include <AssetLoader/loader.h>

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

GLfloat		colors[] =  {
    1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,
    0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,
    0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,
    1, 1, 0,   1, 1, 0,   1, 1, 0,   1, 1, 0,
    1, 0, 1,   1, 0, 1,   1, 0, 1,   1, 0, 1, //changing this from 1, 0, 1 to green
    0, 1, 1,   0, 1, 1,   0, 1, 1,   0, 1, 1
  };

GLRenderer::GLRenderer(GameWindow & win, Camera * camera) {
	cam = camera;
	initialize(win);
}

GLfloat * triangle;
GLfloat cube [] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
};
int vertexCount;

void GLRenderer::initialize(GameWindow & win) {
	world = new WorldModel();
	AssetLoader::loadAsset("../../old/models/cube/", *world);
	vector<Vector3<double>> vertices = world->getVertices();
	vertexCount = vertices.size();
	triangle = new GLfloat[vertexCount*3];
	for (int i = 0; i < vertexCount; i++) {
		triangle[3*i] = (float)vertices[i].x;
		triangle[3*i+1] = (float)vertices[i].y;
		triangle[3*i+2] = (float)vertices[i].z;
	}

	initGL(win);
}

GLuint vertexbuffer = 0;
GLuint programID;

void GLRenderer::initGL(GameWindow & win) {
	glLoadIdentity();
	glViewport(0,0,win.getWidth(),win.getHeight());
	glewInit();
	//programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	glEnable(GL_DEPTH_TEST);
	glFrustum(-1,1,-1,1,2,10000);
	glTranslatef(0,0,-10);
//	gl_font(FL_HELVETICA_BOLD, 16 );



// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount*3, triangle, GL_STATIC_DRAW);

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
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);
}


void GLRenderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(programID);
	glColor3f(1, .07, .57);
	glPushMatrix();
	drawCube();
	glPopMatrix();

}
