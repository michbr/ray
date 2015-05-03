#include "camera.h"
#include <FL/Fl.H>
#include <cmath>
#include <GL/glu.h>

using namespace std;

double MouseSensitivity = 1.0;
int warpMouse(int new_x, int new_y);


Camera::Camera(CameraStructure * camStructure, int width, int height) : position(camStructure->position), direction(camStructure->direction), up(camStructure->up) {
    screenWidth = width;
    screenHeight = height;
}


void Camera::SetViewByMouse(int x, int y) {
    // the coordinates of our mouse coordinates
    int MouseX, MouseY;

    // the middle of the screen in the x direction
    int MiddleX = (screenWidth / 2) + x;

    // the middle of the screen in the y direction
    int MiddleY = (screenHeight / 2) + y;

    // vector that describes mouseposition - center
    Vector3<double> MouseDirection(0, 0, 0);

    // static variable to store the rotation about the x-axis, since
    // we want to limit how far up or down we can look.
    // We don't need to cap the rotation about the y-axis as we
    // want to be able to turn around 360 degrees
    static double CurrentRotationAboutX = 0.0;

    // The maximum angle we can look up or down, in radians
    double maxAngle = 1;

    // This function gets the position of the mouse
    Fl::get_mouse(MouseX, MouseY);

    // if the mouse hasn't moved, return without doing
    // anything to our view
    if ((abs(MouseX - MiddleX) <= 1) && (abs(MouseY - MiddleY) <= 1))
        return;

    // otherwise move the mouse back to the middle of the screen
    warpMouse(MiddleX, MiddleY);
   // cout << "mouse warped to: " << MiddleX << ", " << MiddleY << endl;
//    int newX, newY;
//    Fl::get_mouse(newX, newY);
//    cout << "new position: " << newX << "," << newY << endl;

    // get the distance and direction the mouse moved in x (in
    // pixels). We can't use the actual number of pixels in radians,
    // as only six pixels  would cause a full 360 degree rotation.
    // So we use a mousesensitivity variable that can be changed to
    // vary how many radians we want to turn in the x-direction for
    // a given mouse movement distance

    // We have to remember that positive rotation is counter-clockwise. 
    // Moving the mouse down is a negative rotation about the x axis
    // Moving the mouse right is a negative rotation about the y axis
    //cout << "middleX: " << MiddleX - MouseX<< " middleY: " << MiddleY - MouseY << endl;
    MouseDirection.x = (double)(MiddleX - MouseX) / MouseSensitivity;
    MouseDirection.y = (double)(MiddleY - MouseY) / MouseSensitivity;
    //cout.precision(4);
    cout << "x: " << MouseDirection.x << " y: " << MouseDirection.y << endl;

    CurrentRotationX += MouseDirection.y;

    // We don't want to rotate up more than one radian, so we cap it.
    if (CurrentRotationX > 1) {
        CurrentRotationX = 1;
        return;
    }
    // We don't want to rotate down more than one radian, so we cap it.
    if (CurrentRotationX < -1) {
        CurrentRotationX = -1;
        return;
    } else {
        // get the axis to rotate around the x-axis. 
        Vector3<double> temp = direction;//direction - position;
        Vector3<double> Axis = temp.cross(up);
        // To be able to use the quaternion conjugate, the axis to
        // rotate around must be normalized.
        Axis.normalize();

        // Rotate around the y axis
        rotateCamera(MouseDirection.y, Axis.x, Axis.y, Axis.z);
        // Rotate around the x axis
        rotateCamera(MouseDirection.x, 0, 1, 0);
    }
    //gluLookAt(position.x, position.y, position.z, direction.x, direction.y, direction.z, up.x, up.y, up.z);
    //look();
}

void Camera::rotateCamera(double Angle, double x, double y, double z) {
    Quaternion temp(x * sin(Angle / 2),
            y * sin(Angle / 2),
            z * sin(Angle / 2),
            cos(Angle / 2));

    Quaternion quat_view(direction.x,
            direction.y,
            direction.z,
            0);

    Quaternion result = (temp * quat_view) * temp.conjugate();

    direction.x = result.x - position.x;
    direction.y = result.y - position.y;
    direction.z = result.z - position.z;
    direction.normalize();
//    direction.x = result.x;
//    direction.y = result.y;
//    direction.z = result.z;
}

#if defined _WIN32
#include <Windows.h>
#endif

int warpMouse(int new_x, int new_y) {

#if defined _WIN32
    BOOL result = SetCursorPos(new_x, new_y);
        cout << "x: " << new_x << " y: " << new_y << endl;

    if (result) return 0; // OK

#elif defined __APPLE__
    CGPoint new_pos;
    CGEventErr err;
    new_pos.x = new_x;
    new_pos.y = new_y;
    err = CGWarpMouseCursorPosition(new_pos);
    if (!err) return 0; // OK

#else // Assume this is Xlib
    Window rootwindow = DefaultRootWindow(fl_display);
    XWarpPointer(fl_display, rootwindow, rootwindow, 0, 0, 0, 0,
            new_x, new_y);
    return 0; // Assume OK
#endif

    return -1; // Fail
} // jump_cursor

void LookAt(Vector3<double> target) {
	//direction = (target -position).normal();
}
 //commented due to lack of GL import.  Should exist in gl camera
void Camera::look() {
	//gluLookAt(pos[0], pos[1], pos[2], look[0], look[1], look[2], up[0], up[1], up[2]);
	//cout << "here " << *this << endl;
	//cout << look << endl;
	Matrix<float> M = Matrix<float>(4, 4);
	//cout << "pos: " << pos << endl;
	Vector3<float> posf = Vector3<float>((float)position.x, (float)position.y, (float)position.z);
	Vector3<float> upf =  Vector3<float>((float)up.x, (float)up.y, (float)up.z);

	Vector3<float> F = Vector3<float>(direction.x, direction.y, direction.z);//look - posf;
	//cout << "F: " << F << endl;
	F.normalize();
	up.normalize();
	//cout << "f: " << F << endl;

	Vector3<float> s = upf.cross(F);

	s.normalize();
	//cout << "s: " << s << endl;
	Vector3<float> u = s.cross(F);
	u.normalize();
	//cout << "u: " << u << endl;

	M(0,0) = s[0];
	M(1,0) = s[1];
	M(2,0) = s[2];
	M(3,0) = 0;

	M(0,1) = u[0];
	M(1,1) = u[1];
	M(2,1) = u[2];
	M(3,1) = 0;

	M(0,2) = -F[0];
	M(1,2) = -F[1];
	M(2,2) = -F[2];
	M(3,2) = 0;

	M(0,3) = 0;
	M(1,3) = 0;
	M(2,3) = 0;
	M(3,3) = 1;

	//cout << M << endl;
	//glMatrixMode( GL_PROJECTION );
	//cout << M << endl;
	//glTranslated(-pos[0], -pos[1], -pos[2]);
	glMultMatrixf(M.toArray());
	glTranslated(-position[0], -position[1], -position[2]);
}
