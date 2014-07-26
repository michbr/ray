#include "vertex.h"
#include "MatMath.h"

#include <sstream>
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>

using namespace std;

Vertex::Vertex(double x_value, double y_value, double z_value, double w_value = 1.0) {
	x = x_value;
	y = y_value;
	z = z_value;
	w = w_value;
}

Vertex::Vertex(string line) {
	stringstream s;
	string trash;
	s << line;
	s >> trash;
	vector<double> test;
	while (s.good()) {
		double next;
		s >> next;
		test.push_back(next);
	}
	if (test.size() > 4) {
		cerr << "Vertices cannot have more than 4 coordinates\n";
		exit(1);
	}
	else if (test.size() < 3) {
		cerr << "Vertices must have at least 3 coordinates\n";
		exit(1);
	}
	x = test[0];
	y = test[1];
	z = test[2];
	if(test.size() == 4) {
		w = test[3];
	}
	else {
		w = 1;
	}
}

void Vertex::rotate(double amount, double x_val, double y_val, double z_val) {
	//normalize the axis of rotation
	vector<double> *point = new vector<double>();
	point->push_back(x_val);
	point->push_back(y_val);
	point->push_back(z_val);
	vector<double> * ww = normalize(point);

	
	vector<double> * m = make_perpendicular(ww);
	vector<double> * u = cross_product(ww, m);
	u = normalize(u);


	vector<double> * v = cross_product(ww, u);
	u->push_back(0);
	ww->push_back(0);
	v->push_back(0);
	vector<vector<double> *> R;
	R.push_back(u);
	R.push_back(v);
	R.push_back(ww);
	vector<double> * last = new vector<double>();
	last->push_back(0);
	last->push_back(0);
	last->push_back(0);
	last->push_back(1);
	R.push_back(last);

	vector<vector<double> *> R_t;// = new vector<vector<double> *>();
	for (int i = 0; i < 3; i++) {
		vector<double> * next = new vector<double>();
		next->push_back((*u)[i]);
		next->push_back((*v)[i]);
		next->push_back((*ww)[i]);
		next->push_back(0);
		R_t.push_back(next);	
	}

	double one[] = {cos(amount), -sin(amount), 0, 0};
	double two[] = {sin(amount), cos(amount), 0, 0};
	double three[] = {0, 0, 1, 0};
	double four[] ={0, 0, 0, 1};
	vector<vector<double> *> t;
	t.push_back(new vector<double> (one, one + sizeof(one) / sizeof(double) )); //construct this using arrays
	t.push_back(new vector<double> (two, two + sizeof(two) / sizeof(double) ));
	t.push_back(new vector<double> (three, three + sizeof(three) / sizeof(double) ));
	t.push_back(new vector<double> (four, four + sizeof(four) / sizeof(double) ));

	vector<vector<double> *> p;// = new vector<vector<double>* >();
	
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	
	(p[0])->push_back(x);
	(p[1])->push_back(y);
	(p[2])->push_back(z);
	(p[3])->push_back(w);
	
	vector<vector<double> *> * a = multiply(&R_t, &t);// multiply(&R_t, multiply(&t, multiply(&R, p)));
	vector<vector<double> *> * b = multiply(a, &R);
	vector<vector<double> *> * c = multiply (b, &p);
	
	x = (*(*c)[0])[0];
	y = (*(*c)[1])[0];
	z = (*(*c)[2])[0];
	w = (*(*c)[2])[0];
	fix();
}

void Vertex::arbitrary(vector<vector<double> *> * arb) {
	vector<vector<double> *> p;
	
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	p.push_back(new vector<double>());
	
	(p[0])->push_back(x);
	(p[1])->push_back(y);
	(p[2])->push_back(z);
	(p[3])->push_back(w);
	
	vector<vector<double> *> * result = multiply(arb, &p);
	x = (*(*result)[0])[0];
	y = (*(*result)[1])[0];
	z = (*(*result)[2])[0];
	w = (*(*result)[3])[0];
	fix();
}

void Vertex::translate(double x_val, double y_val, double z_val) {
	x += x_val;
	y += y_val;
	z += z_val;
}

void Vertex::scale(double x_val, double y_val, double z_val) {
	x *= x_val;
	y *= y_val;
	z *= z_val;
}

void Vertex::fix() {
	if (abs(w) > .000001 ) {
	x = x/w;
	y = y/w;
	z = z/w;
	w = w/w;
	}
	//else {
	//	w = 1;
	//}
	
}

double Vertex::get_x() const {
	return x;
}

double Vertex::get_y() const {
	return y;
}

double Vertex::get_z() const {
	return z;
}

double Vertex::get_w() const {
	return w;
}

void Vertex::set_w(double ww) {
w = ww;
}

ostream & Vertex::operator<<(ostream & out) {
	if (w != 1)	return out << "v " << x << " " << y << " " << z << " " << w << "\n";
	else return out << "v " << x << " " << y << " " << z << " " << "\n";
}

std::ostream & operator<<(std::ostream & out, const Vertex & vertex) {
	if (vertex.w != 1) return out << "v " << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.w << "\n";
	else return out << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
}
