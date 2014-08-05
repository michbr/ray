#include "elipse.h"
#include "MatMath.h"
#include "vertex.h"

#include <iostream>
#include <cmath>

using namespace std;
//Elipse::Elipse(double center_x, double center_y, double center_z, double center_w, double x, double y, double z) : {
Elipse::Elipse(string mat_name, Vertex point, double x, double y, double z) : center(point){
	material = mat_name;
	radius_x = x;
	radius_y = y;
	radius_z = z;
	center_point.push_back(center.get_x());
	center_point.push_back(center.get_y());
	center_point.push_back(center.get_z());
	//bool hit = false;
	//cout << "created an elipse at: " << center.get_x() << ", " << center.get_y() << ", " << center.get_z() << endl;
	//center(center_x, center_y, center_z, center_w);
}

void Elipse::set_center() {
	center_point[0] = center.get_x();
	center_point[1] = center.get_y();
	center_point[2] = center.get_z();
}

std::string Elipse::get_material() const {
	return material;
}

vector<double> * Elipse::intersect(const vector<double> * focal_point, const vector<double> * view_point) const {
	vector<double> direction;// = new vector<double>();
	//vector<double> p;// = new vector<double>();
	//cout << "VP length: " << view_point->size() << endl;
	
	direction.push_back((*view_point)[0] - (*focal_point)[0]);
	direction.push_back((*view_point)[1] - (*focal_point)[1]);
	direction.push_back((*view_point)[2] - (*focal_point)[2]);
	
	
	vector<double> line;// = new vector<double>();
	line.push_back(center.get_x() - (*focal_point)[0]);
	line.push_back(center.get_y() - (*focal_point)[1]);
	line.push_back(center.get_z() - (*focal_point)[2]);
	
	//vector<double> * n = normalize(normal);
	//vector<double> * dir = normalize(direction);
	//vector<double> * ln = normalize(line);
	
	double v = dot_product(&line, normalize(&direction));
	double c = magnitude(&line);
	//double b = c*c - v*v;
	double r = radius_x;
	double d = sqrt(r*r - (c*c - v*v));
	double l = v - d;
	//if (l < 4) {
		//cout << "view point: " << (*view_point)[0] << ", " << (*view_point)[1] << ", " << (*view_point)[2] << endl;
		//cout << magnitude(scale(normalize(&direction), l)) << endl;
	//}
	//if (b <= r) {
	//	hit = true;
	//}
	//else {
	//	hit = false;
	//}
	//else hit = true;
	//cout << T << " = " << dot_product(line, n) << "/" << dot_product(direction, n) << endl;
	// ((*focal_point)[0] - vertices[0].get_x())/((*direction)[0]);

	//p.push_back((*focal_point)[0] + (direction[0]*T) );
	//p.push_back((*focal_point)[1] + (direction[1]*T) );
	//p.push_back((*focal_point)[2] + (direction[2]*T) );
	//if (hit) {
		//cout << "l: " << l << endl;
	//}
	//*distance = l;
	return add(focal_point, scale(normalize(&direction), l)); 
}

const vector<double> * Elipse::get_center() const {
	//vector<double> * result = new vector<double>();
	//result->push_back(center.get_x());
	//result->push_back(center.get_y());
	//result->push_back(center.get_z());
	return &center_point;//result;
}

vector<double> * Elipse::get_normal(vector<double> * point) const {
	return subtract(point, get_center());
}

bool Elipse::is_inside(const vector<double> * point) const {
	vector<double> * temp = subtract(point, get_center());
	//if ((magnitude(temp) - radius_x) < .00001 && (magnitude(temp) - radius_x) > .000001) {
	//cout << (magnitude(temp) - radius_x) << endl;
	//}
	if ((magnitude(temp) - radius_x) < .000001 && (radius_x - magnitude(temp)) < .000001) {
		temp->~vector();
		return true;
	}
	temp->~vector();
	return false;
	
	
	/*vector<double> direction;// = new vector<double>();
	//vector<double> p;// = new vector<double>();
	//cout << "VP length: " << view_point->size() << endl;
	
	direction.push_back((*view_point)[0] - (*focal_point)[0]);
	direction.push_back((*view_point)[1] - (*focal_point)[1]);
	direction.push_back((*view_point)[2] - (*focal_point)[2]);
	
	
	vector<double> line;// = new vector<double>();
	line.push_back(center.get_x() - (*focal_point)[0]);
	line.push_back(center.get_y() - (*focal_point)[1]);
	line.push_back(center.get_z() - (*focal_point)[2]);
	
	//vector<double> * n = normalize(normal);
	//vector<double> * dir = normalize(direction);
	//vector<double> * ln = normalize(line);
	
	double v = dot_product(&line, normalize(&direction));
	double c = magnitude(&line);
	double b = sqrt(c*c - v*v);
	double r = radius_x;
	return (b <= r);*/
}

double Elipse::get_radius() const{
	return radius_x;
}
