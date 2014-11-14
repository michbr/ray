#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "rwindow.h"


using namespace std;

GLfloat RWindow::cam_x = 0;
GLfloat RWindow::cam_y = 0;
GLfloat RWindow::cam_z = 0;
GLfloat RWindow::vrp_x = 0;
GLfloat RWindow::vrp_y = 0;
GLfloat RWindow::vrp_z = 0;
GLfloat RWindow::up_x = 0;
GLfloat RWindow::up_y = 0;
GLfloat RWindow::up_z = 0;
GLfloat RWindow::angle = 0;

int RWindow::mouse_x = -1;
int RWindow::mouse_y = -1;

unsigned short int RWindow::usi_hwindow = 0;
unsigned short int RWindow::usi_vwindow = 0;
unsigned short int RWindow::usi_windowx = 0;
unsigned short int RWindow::usi_windowy = 0;

const GLfloat LOOK_SENSITIVITY = .001f;
const GLfloat MOVE_SENSITIVITY = .05f;

int gViewportMode = VIEWPORT_MODE_FULL;

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
    1, 0, 1,   1, 0, 1,   1, 0, 1,   1, 0, 1,
    0, 1, 1,   0, 1, 1,   0, 1, 1,   0, 1, 1
  };

RWindow::RWindow() {
	str_window_title = "Hello World";
	usi_hwindow = 640;
	usi_vwindow = 480;
	usi_windowx = 100;
	usi_windowy = 100;
	RWindow::set_camera(0.f, 0.f, -15.f);
}

RWindow::RWindow(string newtitle) {
	str_window_title = newtitle;
	usi_hwindow = 640;
	usi_vwindow = 480;
	usi_windowx = 100;
	usi_windowy = 100;
	RWindow::set_camera(0.f, 0.f, -15.f);
}

void RWindow::runMainLoop( int val )
{
    //Frame logic
    //update();
    RWindow::render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, RWindow::runMainLoop, val );
}

void RWindow::initGL(int *argc, char** argv) {

	//Initialize FreeGLUT
	glutInit( argc, argv );

	//Create OpenGL 2.1 context
	//    glutInitContextVersion( 2, 1 );

	//Create Double Buffered Window
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize (GetWindowHorizontal(), GetWindowVertical());
	glutInitWindowPosition (GetWindowX(), GetWindowY());
	glutCreateWindow (GetWindowTitle().c_str());

	//Do post window/context creation initialization
	//glViewport( 0.f, 0.f, GetWindowHorizontal(),  GetWindowVertical() );

	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(60, usi_hwindow / (float) usi_vwindow, .01, 999);
	glViewport(0, 0, usi_hwindow, usi_vwindow);

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	//Check for error
	GLenum error = glGetError();

	//Set keyboard handle
	glutReshapeFunc(RWindow::ReshapeFunc);
	glutKeyboardFunc(RWindow::handleKeys );
	glutSpecialFunc(RWindow::specialKeys );

	//Set mouse handle
	glutPassiveMotionFunc(RWindow::PassiveMotion);

	//Set rendering function
	glutDisplayFunc( RWindow::render );
	glEnable(GL_CULL_FACE);
	//Set main loop
	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

	//Start GLUT main loop
	glutMainLoop();

}

void RWindow::SetWindowTitle(string newtitle) {
	str_window_title = newtitle;
}

string RWindow::GetWindowTitle() const {
	return str_window_title;
}

void RWindow::SetWindowHorizontal(unsigned short int newsize) {
	usi_hwindow = newsize;
}

unsigned short int RWindow::GetWindowHorizontal() const {
	return usi_hwindow;
}

void RWindow::SetWindowVertical(unsigned short int newsize) {
	usi_vwindow = newsize;
}

unsigned short int RWindow::GetWindowVertical() const {
	return usi_vwindow;
}

unsigned short int RWindow::GetWindowX() const {
	return usi_windowx;
}

void RWindow::SetWindowX(unsigned short int newsize) {
	usi_windowx = newsize;
}

unsigned short int RWindow::GetWindowY() const {
	return usi_windowy;
}

void RWindow::SetWindowY(unsigned short int newsize) {
	usi_windowy = newsize;
}

RWindow::~RWindow() {
	// remove new variables if any
	// remove self
	delete this; // Make sure pointer is null
}
void RWindow::set_camera(GLfloat x, GLfloat y, GLfloat z) {
	RWindow::cam_x = x;
	RWindow::cam_y = y;
	RWindow::cam_z = z;
	RWindow::vrp_x = 0;
	RWindow::vrp_y = 0;
	RWindow::vrp_z = -14;
	RWindow::up_x = 0;
	RWindow::up_y = 1;
	RWindow::up_z = 0;
}

void RWindow::render()
{
	//static float alpha = 0;

	/* Clear the buffer, clear the matrix */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/* A step backward, then spin the cube */
	gluLookAt(cam_x, cam_y, cam_z, vrp_x, vrp_y, vrp_z, up_x, up_y, up_z);
	// glTranslatef(cam_x, cam_y, cam_z);
	// glRotatef(30, 1, 0, 0);
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
	glutSwapBuffers();
}


/*
** Function called when the window is created or resized
*/
void RWindow::ReshapeFunc(int width, int height)
{
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(60, width / (float) height, .01, 999);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

/*
** Function called when a key is hit
*/
void RWindow::handleKeys( unsigned char key, int x, int y )
{
	//If the user presses q
	if( key == 'q' ) {
		//Cycle through viewport modes
		//gViewportMode++;
		//if( gViewportMode > VIEWPORT_MODE_RADAR ) {
		//    gViewportMode = VIEWPORT_MODE_FULL;
		//}
	}
	if (key == 'v') {
		RWindow::vrp_x = 0 - RWindow::cam_x;
		RWindow::vrp_y = 0 - RWindow::cam_y;
		RWindow::vrp_z = -14 - RWindow::cam_z;
	}
	else {
		cout << (int)key << endl;	
	}
}

void RWindow::specialKeys( int key, int x, int y ) {
	if( key == 100 ) { //left
		cout << "left" << endl;
		GLfloat new_x = RWindow::vrp_y * RWindow::up_z - RWindow::vrp_z * RWindow::up_y;
		GLfloat new_y = RWindow::vrp_z * RWindow::up_x - RWindow::vrp_x * RWindow::up_z;
		GLfloat new_z = RWindow::vrp_x * RWindow::up_y - RWindow::vrp_y * RWindow::up_x;

		GLfloat magnitude = sqrt(new_x*new_x + new_y*new_y + new_z*new_z);

		new_x = new_x / magnitude;
		new_y = new_y / magnitude;
		new_z = new_z / magnitude;

		RWindow::cam_x = RWindow::cam_x - new_x * MOVE_SENSITIVITY;
		RWindow::cam_y = RWindow::cam_y - new_y * MOVE_SENSITIVITY;
		RWindow::cam_z = RWindow::cam_z - new_z * MOVE_SENSITIVITY;
		
	}
	else if( key == 102 ) { //right
		cout << "right" << endl;
		GLfloat new_x = RWindow::vrp_y * RWindow::up_z - RWindow::vrp_z * RWindow::up_y;
		GLfloat new_y = RWindow::vrp_z * RWindow::up_x - RWindow::vrp_x * RWindow::up_z;
		GLfloat new_z = RWindow::vrp_x * RWindow::up_y - RWindow::vrp_y * RWindow::up_x;

		GLfloat magnitude = sqrt(new_x*new_x + new_y*new_y + new_z*new_z);

		new_x = new_x / magnitude;
		new_y = new_y / magnitude;
		new_z = new_z / magnitude;

		RWindow::cam_x = RWindow::cam_x + new_x * MOVE_SENSITIVITY;
		RWindow::cam_y = RWindow::cam_y + new_y * MOVE_SENSITIVITY;
		RWindow::cam_z = RWindow::cam_z + new_z * MOVE_SENSITIVITY;
	}
	else if( key == 101 ) { //up
		cout << "up" << endl; 
		GLfloat new_x = RWindow::vrp_x;
		GLfloat new_y = RWindow::vrp_y;
		GLfloat new_z = RWindow::vrp_z;

		GLfloat magnitude = sqrt(new_x*new_x + new_y*new_y + new_z*new_z);

		new_x = new_x / magnitude;
		new_y = new_y / magnitude;
		new_z = new_z / magnitude;

		RWindow::cam_x = RWindow::cam_x - new_x * MOVE_SENSITIVITY;
		RWindow::cam_y = RWindow::cam_y - new_y * MOVE_SENSITIVITY;
		RWindow::cam_z = RWindow::cam_z - new_z * MOVE_SENSITIVITY;
	}
	else if( key == 103 ) { //down
		cout << "down" << endl; 
		GLfloat new_x = RWindow::vrp_x;
		GLfloat new_y = RWindow::vrp_y;
		GLfloat new_z = RWindow::vrp_z;

		GLfloat magnitude = sqrt(new_x*new_x + new_y*new_y + new_z*new_z);

		new_x = new_x / magnitude;
		new_y = new_y / magnitude;
		new_z = new_z / magnitude;

		RWindow::cam_x = RWindow::cam_x + new_x * MOVE_SENSITIVITY;
		RWindow::cam_y = RWindow::cam_y + new_y * MOVE_SENSITIVITY;
		RWindow::cam_z = RWindow::cam_z + new_z * MOVE_SENSITIVITY;
	}
	else {
		cout << (int)key << endl;	
	}
}

void RWindow::PassiveMotion( int x, int y ) {
	if (RWindow::mouse_x < 0 || RWindow::mouse_y < 0) {
		RWindow::mouse_x = x;
		RWindow::mouse_y = y;
	}

	int prev_x = RWindow::mouse_x;
	int prev_y = RWindow::mouse_y;
	
	RWindow::mouse_x = x;
	RWindow::mouse_y = y;

	GLfloat move_x = x - prev_x;
	GLfloat move_y = y - prev_y;

	calc_angle(move_x, RWindow::cam_x, RWindow::cam_z, &RWindow::vrp_x, &RWindow::vrp_z);
	calc_angle(move_y, RWindow::cam_y, RWindow::cam_z, &RWindow::vrp_y, &RWindow::vrp_z);
	
}

GLfloat RWindow::calc_angle(GLfloat move, GLfloat cam_1, GLfloat cam_2, GLfloat *vrp_1, GLfloat *vrp_2 ) {
	GLfloat cam_x = *vrp_1 - cam_1;
	GLfloat cam_z = RWindow::vrp_z - RWindow::cam_z;

	GLfloat magnitude = sqrt(cam_x*cam_x + cam_z*cam_z);

	GLfloat angle = acos(cam_z/magnitude);
	if (cam_x < 0) {
		angle = -abs(angle);
	}
	else {
		angle = abs(angle);		
	}

	*vrp_1 = sin(angle - LOOK_SENSITIVITY*move) + cam_1;
	RWindow::vrp_z = cos(angle - LOOK_SENSITIVITY*move) + RWindow::cam_z;
}

void RWindow::init () {
	/* select clearing (background) color */
	glClearColor (0.0, 0.0, 0.0, 0.0);

	/* initialize viewing values */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, -1.0);
};

/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA). Open window with "hello"
* in its title bar. Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv) {

	// Code to initialize window. Normally this would be in another class
	RWindow *testWindow = new RWindow("Dragon");
	testWindow->initGL(&argc, argv);
	delete testWindow;

	return 0; /* ISO C requires main to return int. */

};
