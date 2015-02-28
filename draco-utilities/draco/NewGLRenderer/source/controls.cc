#include "controls.h"
#include "dragon.h"

using namespace std;

const GLfloat LOOK_SENSITIVITY = .01f;

Controls::Controls(DragonEngine & eng, Camera & camera) {
	engine = &eng;
	cam = &camera;
	mouse_x = -1;
	mouse_y = -1;
}

void Controls::keyPress(int keyCode) {
	/*if( key == 100 ) { //left
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
	}*/
}

void Controls::motionEvent(int x, int y) {
	if (mouse_x < 0 || mouse_y < 0) {
		mouse_x = x;
		mouse_y = y;
	}

	int prev_x = mouse_x;
	int prev_y = mouse_y;
	
	mouse_x = x;
	mouse_y = y;

	GLfloat move_x = x - prev_x;
	GLfloat move_y = y - prev_y;
	
	/*GLfloat qx = 0;
	GLfloat qy = 1 * sin(move_x * LOOK_SENSITIVITY/2.0);
	GLfloat qz = 0;
	GLfloat qw = cos(move_x * LOOK_SENSITIVITY/2.0);*/
	
	
	//cout << *cam << endl;
	cam->rotate(-move_y * LOOK_SENSITIVITY, 1 );
	cam->rotate(move_x * LOOK_SENSITIVITY, 0 );
	
	//calc_angle(move_x, RWindow::cam_x, RWindow::cam_z, &RWindow::vrp_x, &RWindow::vrp_z);
	//calc_angle(move_y, RWindow::cam_y, RWindow::cam_z, &RWindow::vrp_y, &RWindow::vrp_z);
	
	//cout << "key: " << keyCode << endl;
}
