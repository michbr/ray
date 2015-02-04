
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "camera.h"

using namespace std;


// initializes the camera with a number of values
Camera::Camera(const string &name, const Vec3 &position, const Vec3 &normal, const Vec3 &up, double near, double far):
	name(name),
	position(position),
	normal(normal.normal()),
	up(up.normal()),
	near(near),
	far(far) {}

// outputs the values or state of the camera
ostream &operator<<(ostream &out, const Camera &cam) {
	return out << "pos:" << cam.position << ", norm:" << cam.normal << ", up:" << cam.up << ", n:" << cam.near << ", f:" << cam.far << "";
}
