
#include "glRenderer.h"
//#include "loadShader.h"

using namespace std;

void GLRenderer::setWorld(WorldModel &world) {
    this->world = &world;
    world.addRenderer(*this);
}

WorldModel& GLRenderer::getWorld() {
    return *world;
}

void GLRenderer::initGL(int width, int height, int offsetX, int offsetY) {
    x = offsetX;
    y = offsetY;
    glLoadIdentity();
    glViewport(0, 0, width, height);
    glewInit();
    //programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

    glEnable(GL_DEPTH_TEST);
    glFrustum(-1, 1, -1, 1, 2, 10000);
    glTranslatef(0, 0, -10);
    //	gl_font(FL_HELVETICA_BOLD, 16 );
}

void drawBuffer(GLuint buffer, GLsizei vertexCount) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(
            0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            (void*) 0 // array buffer offset
            );

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, vertexCount); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

void GLRenderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glUseProgram(programID);
    glColor3f(1, .07, .57);
    glPushMatrix();

    // render all buffers
    glEnableVertexAttribArray(0);
    for (auto buffer : buffers) {
        drawBuffer(buffer.second.buffer, buffer.second.vertexCount);
    }
    glDisableVertexAttribArray(0);


    glPopMatrix();
    currentCam->SetViewByMouse(x, y);
    //currentCam->look();


}

void GLRenderer::addObject(SceneObject *object) {
    GLuint buffer = buffers[object].buffer;
    if (buffer == 0) {
        // generate the new buffer
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        buffers[object].buffer = buffer;
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
    buffers[object].vertexCount = coords.size() / 3;
    glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * coords.size(), coords.data(), GL_STATIC_DRAW);
}

void GLRenderer::removeObject(SceneObject *object) {
    GLuint buffer = buffers[object].buffer;
    buffers.erase(object);
    if (buffer == 0) return;
    glDeleteBuffers(1, &buffer);
}

void GLRenderer::addCamera(CameraStructure *cam) {
    currentCam = new Camera(cam, 500, 500);
}