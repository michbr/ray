#include "camera.h"

#include <iostream>
#include <cmath>

using namespace std;

Camera::Camera(string cname, double d, double x_val, double y_val, double z_val, Vector3<double> * normal, Vector3<double> * vup) {
	name = cname;
	x = x_val;
	y = y_val;
	z = z_val;
	focal_length = d;
	vpn = normal;
	v_up = vup;
	//has_frame = false;
	
	Vector3<double> n = vpn->normalize();
	fp = new Vector3<double>(
			(x + n[0]*focal_length),
			(y + n[1]*focal_length),
			(z + n[2]*focal_length));
}

string Camera::get_name() {
	return name;
}

Vector3<double> Camera::getPos() {
	Vector3<double> a = Vector3<double>(x, y, z);
	return a;
}

Vector3<double> Camera::getFocalPoint() {
	Vector3<double> a = Vector3<double>( (*fp)[0], (*fp)[1], (*fp)[2]);
	return a;
}

Vector3<double> Camera::getHorizontalAxis() {
	Vector3<double> n = vpn->normalize();
	Vector3<double> u = v_up->normalize().cross(n).normalize();
	return u;
}

Vector3<double> Camera::getVerticalAxis() {
	Vector3<double> n = vpn->normalize();
	Vector3<double> u = v_up->normalize().cross(n).normalize();
	Vector3<double> v = n.cross(u).normalize();
	
	return v;
}
