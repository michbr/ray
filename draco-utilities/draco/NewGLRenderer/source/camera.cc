#include "camera.h"
#include <FL/Fl.H>
#include <cmath>

double MouseSensitivity = 1.0;

Camera::Camera(CameraStructure * camStructure, int width, int height) : position(camStructure->position), direction(camStructure->direction), up(camStructure->up) {
    screenWidth = width;
    screenHeight = height;
}

int warpMouse(int new_x, int new_y);

void Camera::SetViewByMouse() {
    // the coordinates of our mouse coordinates
    int MouseX, MouseY;

    // the middle of the screen in the x direction
    int MiddleX = screenWidth / 2;

    // the middle of the screen in the y direction
    int MiddleY = screenHeight / 2;

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
    get_mouse(&MouseX, &MouseY);

    // if the mouse hasn't moved, return without doing
    // anything to our view
    if ((MouseX == MiddleX) && (MouseY == MiddleY))
        return;

    // otherwise move the mouse back to the middle of the screen
    warpMouse(MiddleX, MiddleY);

    // get the distance and direction the mouse moved in x (in
    // pixels). We can't use the actual number of pixels in radians,
    // as only six pixels  would cause a full 360 degree rotation.
    // So we use a mousesensitivity variable that can be changed to
    // vary how many radians we want to turn in the x-direction for
    // a given mouse movement distance

    // We have to remember that positive rotation is counter-clockwise. 
    // Moving the mouse down is a negative rotation about the x axis
    // Moving the mouse right is a negative rotation about the y axis
    MouseDirection.x = (MiddleX - MouseX) / MouseSensitivity;
    MouseDirection.y = (MiddleY - MouseY) / MouseSensitivity;

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
        Vector3<double> temp = direction - position;
        Vector3<double> Axis = temp.cross(up);
        // To be able to use the quaternion conjugate, the axis to
        // rotate around must be normalized.
        Axis.normalize();

        // Rotate around the y axis
        rotateCamera(MouseDirection.y, Axis.x, Axis.y, Axis.z);
        // Rotate around the x axis
        rotateCamera(MouseDirection.x, 0, 1, 0);
    }
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

    direction.x = result.x;
    direction.y = result.y;
    direction.z = result.z;
}

#if defined _WIN32
#include <Windows.h>
#endif

int warpMouse(int new_x, int new_y) {

#if defined _WIN32
    BOOL result = SetCursorPos(new_x, new_y);
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
