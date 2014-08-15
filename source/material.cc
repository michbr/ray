#include "material.h"

#include "MatMath.h"

#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;
//Broke up the material vector into Ka, Kd, and Ks.
Material::Material(string n) {
	name = n;
    Ka = new vector<double>();
	Kd = new vector<double>();
	Ks = new vector<double>();
}

void Material::setAmbient(std::vector<double> * a) {
	Ka = a;
}
void Material::setDiffuse(std::vector<double> * a) {
	Kd = a;
}

void Material::setSpecular(std::vector<double> * a) {
	Ks = a;
}

void Material::setShininess(double a) {
	Ns = a;
}

void Material::setTransparency(double a) {
	Tr = a;
}

std::string Material::getName() {
	return name;
}

/*void Material::add_material(fstream & input) {
    int count = 0;
    while (count < 5 && input.good()) {
		stringstream s;
		char  c_line[150];
		input.getline(c_line, 150);
		string line = c_line; 
		line = line.substr(0, line.find_first_of('#'));
		s << line;
		string trash;
		double r, g, b;
		if (count < 3) {
			s >> trash >> r >> g >> b;
		}
		else {
			s >> trash >> r;
		}
		if (!s.bad() && !s.fail()) {
			vector<double> * row = new vector<double>();
			row->push_back(r);
			row->push_back(g);
			row->push_back(b);
			//materials->push_back(row);
			if (trash.compare("Ka") == 0) {
				Ka->push_back(row);
			}
			if (trash.compare("Kd") == 0) {
				Kd->push_back(row);
			}
			if (trash.compare("Ks") == 0) {
				Ks->push_back(row);
			}
			if (trash.compare("Ns") == 0) {
				Ns.push_back(r);
			}
			if (trash.compare("Tr") == 0) {
				// cout << "found Tr for: " << names[names.size() - 1] << endl;
				Tr.push_back(r);
			}
		}
		else {
			cerr << "Failed to read material file." << endl;
			exit(1);
		}
		count++;
    }
}*/

/*void Material::load_materials(string file_name) {
    fstream input;
    input.open(file_name.c_str());
    string line;
    stringstream s;
    while(input.good()) {
		char c_line[150];
		input.getline(c_line, 150);
		string line = c_line; 
		line = line.substr(0, line.find_first_of('#'));
		s << line;
		string flag;
		string name;
		s >> flag >> name;
		//cout << flag << endl;
		if (flag.compare("newmtl") == 0) {
			names.push_back(name);
			//cout << "adding material: " << name << endl;
			add_material(input);
		}
    }
}*/

vector<int> * Material::color_ambient(const vector<int> * light_color) const {
	//vector<vector<double> *> color;
	//	vector<double> row1;
	//		row1.push_back((*light_color)[0]);
	//	vector<double> row2;
	//		row2.push_back((*light_color)[1]);
	//	vector<double> row3;
	//		row3.push_back((*light_color)[2]);
	//	color.push_back(&row1);
	//	color.push_back(&row2);
	//	color.push_back(&row3);
	//vector<vector<double> * > * result = multiply(prepare_matrix((*Ka)[index]), &color);
	vector<int> * final = new vector<int>();
	//final->push_back(round((*(*result)[0])[0]));
	//final->push_back(round((*(*result)[1])[0]));
	//final->push_back(round((*(*result)[2])[0]));
	//result->~vector();
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	final->push_back(round((*Ka)[0]*r));
	final->push_back(round((*Ka)[1]*g));
	final->push_back(round((*Ka)[2]*b));
	return final;
}

vector<int> * Material::color_diffuse(const vector<int> * light_color, double cos) const {
	/*vector<vector<double> *> color;
		vector<double> row1;
			row1.push_back((*light_color)[0]);
		vector<double> row2;
			row2.push_back((*light_color)[1]);
		vector<double> row3;
			row3.push_back((*light_color)[2]);
		color.push_back(&row1);
		color.push_back(&row2);
		color.push_back(&row3);
	vector<vector<double> * > * result = multiply(prepare_matrix((*Kd)[index]), &color);*/
	vector<int> * final = new vector<int>();
	//final->push_back(round((*(*result)[0])[0] * abs(cos)));
	//final->push_back(round((*(*result)[1])[0] * abs(cos)));
	//final->push_back(round((*(*result)[2])[0] * abs(cos)));
	//cout << "r: " << (*light_color)[0] << " g: " << (*light_color)[1] << " b: " << (*light_color)[2] << endl;
	//cout << "Kdg " << (*(*Kd)[index])[1] << endl;
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	final->push_back(round((*Kd)[0]*r * abs(cos)));
	final->push_back(round((*Kd)[1]*g * abs(cos)));
	final->push_back(round((*Kd)[2]*b * abs(cos)));
	return final;
}

vector<int> * Material::color_specular(const vector<int> * light_color, double cos) const {
	vector<int> * final = new vector<int>();
	double alpha = Ns;//[index];
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	//cout << "alpha: " << alpha << endl;
	final->push_back(round((*Ks)[0]*r * pow(cos, alpha)));
	final->push_back(round((*Ks)[1]*g * pow(cos, alpha)));
	final->push_back(round((*Ks)[2]*b * pow(cos, alpha)));
	return final;
}

vector<int> * Material::color_reflection(const vector<int> * light_color) const {
	vector<int> * final = new vector<int>();
	double alpha = Ns;//[index];
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	//cout << "alpha: " << alpha << endl;
	final->push_back(round((*Ks)[0]*r));
	final->push_back(round((*Ks)[1]*g));
	final->push_back(round((*Ks)[2]*b));
	return final;
}

vector<vector<double> *> * Material::prepare_matrix(vector<double> * properties) const {
	vector<vector<double> *> * result = new vector<vector<double> *>();
	vector<double> * row1 = new vector<double>();
		row1->push_back((*properties)[0]);
		row1->push_back(0);
		row1->push_back(0);
	vector<double> * row2 = new vector<double>();
		row2->push_back(0);
		row2->push_back((*properties)[1]);
		row2->push_back(0);
	vector<double> * row3 = new vector<double>();
		row3->push_back(0);
		row3->push_back(0);
		row3->push_back((*properties)[2]);
	result->push_back(row1);
	result->push_back(row2);
	result->push_back(row3);
	return result;
}

double Material::get_tr () const {
	return Tr;
}