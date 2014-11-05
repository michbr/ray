#include "camera.h"
#include "MatMath.h"
#include "vertex.h"

#include <iostream>
#include <cmath>

using namespace std;

Camera::Camera(string cname, double d, double x_val, double y_val, double z_val, vector<double> * normal, std::vector<double> * vup) {
	name = cname;
	x = x_val;
	y = y_val;
	z = z_val;
	focal_length = d;
	vpn = normal;
	v_up = vup;
	//has_frame = false;
	fp = new vector<double>();
	vector<double> * n = normalize(vpn);
	fp->push_back(x + (*n)[0]*focal_length);
	fp->push_back(y + (*n)[1]*focal_length);
	fp->push_back(z + (*n)[2]*focal_length);
	//image = new vector<vector<int> *>();
	delete(n);
	//n->~vector();
}

string Camera::get_name() {
	return name;
}

vector<double> * Camera::getPos() {
	vector<double> * a = new vector<double>();
	a->push_back(x);
	a->push_back(y);
	a->push_back(z);
	return a;
}

vector<double> * Camera::getFocalPoint() {
	vector<double> * a = new vector<double>();
	a->push_back((*fp)[0]);
	a->push_back((*fp)[1]);
	a->push_back((*fp)[2]);
	return a;
}

vector<double> * Camera::getHorizontalAxis() {
	vector<double> * n = normalize(vpn);
	vector<double> * u = normalize(cross_product(normalize(v_up), n));
	
	return u;
}

vector<double> * Camera::getVerticalAxis() {
	vector<double> * n = normalize(vpn);
	vector<double> * u = normalize(cross_product(normalize(v_up), n));
	vector<double> * v = normalize(cross_product(n, u));
	return v;
}
