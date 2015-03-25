#include "glRenderer.h"
#include "loadShader.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <GL/glext.h>

#include <iostream>
#include <AssetLoader/loader.h>

using namespace std;


GLfloat	vertices[] = {
	1, 1, 1,    1, -1,  1,    1,  -1,  -1,    1,  1, -1,
	-1, 1, 1,   -1, 1,  -1,   -1,  -1,  -1,   -1,  -1, 1,
	1, -1, 1,   -1, -1,  1,    -1, -1,  -1,    1, -1, -1,
	-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
	-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
	1, 1,  1,   -1,  1,  1,    -1,  -1,  1,    1, -1,  1
};

GLfloat	colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
	1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
	1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, //changing this from 1, 0, 1 to green
	0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1
};

GLRenderer::GLRenderer(GameWindow & win, Camera * camera) {
	cam = camera;
	initialize(win);
}

GLfloat * triangle;
//GLfloat cube [] = {
//		-1.0f, -1.0f, 0.0f,
//		1.0f, -1.0f, 0.0f,
//		0.0f,  1.0f, 0.0f,
//};
int vertexCount;

void GLRenderer::initialize(GameWindow & win) {
//	AssetLoader::loadAsset(assetFolder, *world);
//	vector<Vector3<double>> vertices = world->getVertices();
//	vertexCount = vertices.size();
//	triangle = new GLfloat[vertexCount*3];
//	for (int i = 0; i < vertexCount; i++) {
//		triangle[3*i] = (float)vertices[i].x;
//		triangle[3*i+1] = (float)vertices[i].y;
//		triangle[3*i+2] = (float)vertices[i].z;
//	}

	initGL(win);
}

void GLRenderer::setWorld(WorldModel &world) {
	this->world = &world;
	world.addRenderer(*this);
}

GLuint vertexbuffer = 0;
//GLuint programID;

void GLRenderer::initGL(GameWindow & win) {
	glLoadIdentity();
	glViewport(0,0,win.getWidth(),win.getHeight());
	glewInit();
	//programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	glEnable(GL_DEPTH_TEST);
	glFrustum(-1,1,-1,1,2,10000);
	glTranslatef(0,0,-10);
//	gl_font(FL_HELVETICA_BOLD, 16 );



//	// Generate 1 buffer, put the resulting identifier in vertexbuffer
//	glGenBuffers(1, &vertexbuffer);
//
//	// The following commands will talk about our 'vertexbuffer' buffer
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//
//	// Give our vertices to OpenGL.
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount*3, triangle, GL_STATIC_DRAW);

}

//#define v3f(x) glVertex3fv(x)



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

//	drawCube();
	// render all buffers


	glPopMatrix();

}

void GLRenderer::addObject(SceneObject *object) {
	GLuint buffer = buffers[object];
	if (buffer == 0) {
		// generate the new buffer
		glGenBuffers(1, &buffer);
//		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		buffers[object] = buffer;
	}

	// Give our vertices to OpenGL
	vector<GLfloat> coords;
	for (int i = 0; i < object->getFaces().size(); i++) {
		vector<Vector3<double>> subset = object->getFaces()[i]->getVertices();
		for (int j = 0; j < subset.size(); j++) {
			coords.push_back(subset[j].x);
			coords.push_back(subset[j].y);
			coords.push_back(subset[j].z);
		}
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * coords.size(), coords.data(), GL_STATIC_DRAW);
}
void GLRenderer::removeObject(SceneObject *object) {
	GLuint buffer = buffers[object];
	buffers.erase(object);
	if (buffer == 0) return;
	glDeleteBuffers(1, &buffer);
}