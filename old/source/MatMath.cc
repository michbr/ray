#include "MatMath.h"
#include <cmath>
#include <iostream>

using namespace std;


vector<double> * normalize(const vector<double> * point) { //re-think this
	double magnitude = sqrt(((*point)[0]*(*point)[0]) + ((*point)[1]*(*point)[1]) + ((*point)[2]*(*point)[2]));
	vector<double> * normal = new vector<double>();
	normal->push_back((*point)[0]/magnitude);
	normal->push_back((*point)[1]/magnitude);
	normal->push_back((*point)[2]/magnitude);
	return normal;
}

vector<double> * cross_product(const vector<double> * a, const vector<double> * b) {
	vector<double> * result = new vector<double>();
	result->push_back( ((*a)[1]*(*b)[2])- ((*a)[2]*(*b)[1]) );
	result->push_back( ((*a)[2]*(*b)[0])- ((*a)[0]*(*b)[2]) );
	result->push_back( ((*a)[0]*(*b)[1])- ((*a)[1]*(*b)[0]) );
	return result;
}

double dot_product(const vector<double> * a, const vector<double> * b) {
	return ((*a)[0] * (*b)[0]) + ((*a)[1] * (*b)[1]) + ((*a)[2] * (*b)[2]); 
}

vector<vector<double>*> * multiply(const vector<vector<double> *> * a, const vector<vector<double> *> 
* b) {
	vector<vector<double> *> * result = new vector<vector<double> *>();
	for (int i = 0; i < a->size(); i++) { // For each new row
		vector<double> * row = new vector<double>();
		for (int j = 0; j < (*b)[0]->size(); j++) { //for each new column in the current new row
			double col_val = 0;
			for (int k = 0; k < (*a)[0]->size(); k++) {
					col_val = col_val + (*((*a)[i]))[k] * ((*(*b)[k])[j]);
			}
			row->push_back(col_val);
		}
		result->push_back(row);
	}
	return result;
}

vector<double>* make_perpendicular(const vector<double> * point) {
	int index = 0;
	vector<double> * axis =  new vector<double>();
	axis->push_back((*point)[0]);
	axis->push_back((*point)[1]);
	axis->push_back((*point)[2]);
	double min = (*axis)[0];
	
	for (int i = 1; i < 3; i++) {
		if ((*axis)[i] < min) {
			index = i;
			min = (*axis)[i];
		}
	}
	
	(*axis)[index] = 1;
	return normalize(axis);
}

double magnitude(const std::vector<double> * vector) {
	return sqrt((*vector)[0]*(*vector)[0] + (*vector)[1]*(*vector)[1] + (*vector)[2]*(*vector)[2]);
}

std::vector<double> * add(const std::vector<double> * a, const std::vector<double> * b) {
	vector<double> * result = new vector<double>();
	result->push_back((*a)[0] + (*b)[0]);
	result->push_back((*a)[1] + (*b)[1]);
	result->push_back((*a)[2] + (*b)[2]);
	return result;
}

std::vector<double> * subtract(const std::vector<double> * a, const std::vector<double> * b) {
	vector<double> * result = new vector<double>();
	result->push_back((*a)[0] - (*b)[0]);
	result->push_back((*a)[1] - (*b)[1]);
	result->push_back((*a)[2] - (*b)[2]);
	return result;
}

vector<double> * scale(const vector<double> * a, double scalar) {
	vector<double> * result = new vector<double>();
	result->push_back((*a)[0]*scalar);
	result->push_back((*a)[1]*scalar);
	result->push_back((*a)[2]*scalar);
	return result;
}

bool is_equal(const vector<double> * a, const vector<double> * b) {
	//cout << "got here" << endl;
	//cout << abs((*a)[0] - (*b)[0]) << " " << abs((*a)[1] - (*b)[1]) << " " << abs((*a)[2] - (*b)[2]) << endl;
	if ((abs((*a)[0] - (*b)[0]) < .00001)  && (abs((*a)[1] - (*b)[1]) < .00001) && (abs((*a)[2] - (*b)[2]) < .00001)) {
		return true;
	}
	else return false;
}
