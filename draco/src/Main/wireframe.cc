#include "wireframe.h"

#include <iostream>

using namespace std;

Wireframe::Wireframe(std::string cname, double x_min, double y_min, double x_max, double y_max, int depth = 1) {
	name = cname;
	min_x = x_min;
	min_y = y_min;
	max_x = x_max;
	max_y = y_max;
	r_depth = depth;
	//cout << "cam: " << x_min << " " << y_min << " " << x_max << " " << y_max << endl;
	
}

double Wireframe::get_minx() const {
return min_x;
}

double Wireframe::get_miny() const {
return min_y;
}
double Wireframe::get_maxx() const {
return max_x;
}
double Wireframe::get_maxy() const {
return max_y;
}

int Wireframe::get_depth() {
	return r_depth;
}