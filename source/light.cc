#include "light.h"
#include "MatMath.h"

//populated this stuff
#include <cmath>
#include <iostream>

using namespace std;

Light::Light(double x, double y, double z, double w, int r, int g, int b) : center(x, y, z, w){
	//cout << "creating light: " << r << " " << g << " " << b << endl;
	/*if (center.get_w() == 0) {
		double x_pos = center.get_x()*9999 - center.get_x();
		double y_pos = center.get_y()*9999 - center.get_y();
		double z_pos = center.get_z()*9999 - center.get_z();
		center.translate(x_pos, y_pos, z_pos);
	}*/

	//cout << "after cond" << endl;
	center_point.push_back(center.get_x());
	center_point.push_back(center.get_y());
	center_point.push_back(center.get_z());
	//cout << "created c_p" << endl;
	color.push_back(r);
	color.push_back(g);
	color.push_back(b);
	//cout << "pushed" << endl;
}

void Light::set_center() {
	center_point[0] = center.get_x();
	center_point[1] = center.get_y();
	center_point[2] = center.get_z();
}

const std::vector<int> * Light::get_color() const{
	return &color;
}

double Light::get_x() const {
	return center.get_x();
}

double Light::get_y() const {
	return center.get_y();
}

double Light::get_z() const {
	return center.get_z();
}

double Light::get_w() const {
	return center.get_w();
}

const vector<double> * Light::get_center() const{
	//vector<double> * result = new vector<double>();
	//result->push_back(center.get_x());
	//result->push_back(center.get_y());
	//result->push_back(center.get_z());
	return &center_point;//result;
}

bool Light::is_blocked(vector<double> * point, const vector<Face *> & faces, const vector<Elipse *> & elipses) {
	//vector<double> * ray 
//	double d;
	//if (center.get_w() == 0) {
		//d = magnitude();
	//}
	vector<double> * sbt = subtract(point, get_center());
	double d = magnitude(sbt);
	delete(sbt);
	for	(int i = 0; i < faces.size(); i++) {
		double T;
		vector<double> * temp = faces[i]->intersect(point, get_center(), &T); //switched these
		if (faces[i]->is_inside(temp)) {
			vector<double> * sbt = subtract(temp, get_center());
			double d1 = magnitude(sbt);
			sbt->clear();
			sbt->~vector();
			if ((d - d1) < 0.000001 && (d1 - d) < .000001) {
				
			}
			else if (d > d1) {
			delete(temp);
			return true;
			}
		}
		delete(temp);
	//	temp->clear();
	//	temp->~vector();
	}
	
	for	(int i = 0; i < elipses.size(); i++) {
		vector<double> * temp = elipses[i]->intersect(point, get_center());
		if (elipses[i]->is_inside(temp)) {
			double d1 = magnitude(subtract(temp, get_center()));
			if ((d - d1) < 0.000001 && (d1 - d) < .000001) {
				
			}
			else if (d > d1) {
			return true;
			}
		}
		temp->~vector();
	}
	return false;
}
