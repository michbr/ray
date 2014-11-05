#include "dragon.h"
#include "controls.h"

using namespace std;

DragonEngine::DragonEngine() {
	
}

void DragonEngine::initWindow(int w, int h) {
	win	= new GameWindow(w, h);
}

void DragonEngine::placeCamera
(GLfloat c_x, GLfloat c_y, GLfloat c_z,	// location of the camera
 GLfloat v_x, GLfloat v_y, GLfloat v_z,	// look-at point
 GLfloat u_x, GLfloat u_y, GLfloat u_z) {	// up vector	

	cam = new Camera<GLfloat>(c_x, c_y, c_z, v_x, v_y, v_z, u_x, u_y, u_z);
	initRenderer();
	controls = new Controls(*this, *cam);
}

void DragonEngine::initRenderer() {
	rend = new Renderer(*win, cam);
}

void DragonEngine::render() {
	//cout << *cam << endl;
	rend->render();
	//cout << *cam << endl;
}

void DragonEngine::event(int keyCode) {
	controls->keyPress(keyCode);
}

void DragonEngine::motionEvent(int x, int y) {
	controls->motionEvent(x, y);
}