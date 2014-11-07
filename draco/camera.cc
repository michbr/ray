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
	fp = new Vector3<double>();
	Vector3<double> * n;
	Vector3<double>::normalize(*vpn, *n);
	(*fp)[0] = (x + (*n)[0]*focal_length);
	(*fp)[1] = (y + (*n)[1]*focal_length);
	(*fp)[2] = (z + (*n)[2]*focal_length);
	//image = new vector<vector<int> *>();
	delete(n);
	//n->~vector();
}

string Camera::get_name() {
	return name;
}

Vector3<double> * Camera::getPos() {
	Vector3<double> * a = new Vector3<double>();
	(*a)[0] = x;
	(*a)[1] = y;
	(*a)[2] = z;
	return a;
}

Vector3<double> * Camera::getFocalPoint() {
	Vector3<double> * a = new Vector3<double>();
	(*a)[0] = (*fp)[0];
	(*a)[1] = (*fp)[1];
	(*a)[2] = (*fp)[2];
	return a;
}

Vector3<double> * Camera::getHorizontalAxis() {
	Vector3<double> n = Vector3<double>();
	Vector3<double>::normalize(*vpn, n);
	Vector3<double> * u;
	Vector3<double> temp;
	Vector3<double>::normalize(*v_up, temp);
	Vector3<double>::cross(temp, n, temp);
	Vector3<double>::normalize(temp, *u);
	return u;
}

Vector3<double> * Camera::getVerticalAxis() {
	Vector3<double> n;
	Vector3<double>::normalize(*vpn, n);
	Vector3<double> u;
	Vector3<double> temp;
	Vector3<double>::normalize(*v_up, temp);
	Vector3<double>::cross(temp, n, temp);
	Vector3<double>::normalize(temp, u);
	Vector3<double>::cross(n, u, temp);
	Vector3<double> * v;
	Vector3<double>::normalize(temp, *v);
	return v;
}
