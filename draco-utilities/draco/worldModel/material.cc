
#include "material.h"

#include <sstream>
#include <iostream>
#include <cmath>


using namespace std;
//Broke up the material vector into Ka, Kd, and Ks.
Material::Material(string n) : Ka(0,0,0), Kd(0,0,0), Ks(0,0,0) {
	name = n;
}

void Material::addTexture(string texPath) {
//        vector<string> blah = head->getTextures();
        //char * cwd = new char[255];
        //getcwd(cwd, 255);
        //texPath.append(cwd);
        //texPath.append("/");
        //texPath.append(blah[i]);
//	cout << "Adding texture: " << texPath << endl;
//	textures.push_back(TextureLoader::loadTexture(texPath));
	/*for (int i = 0; i < 5; i++ ) {
		for (int j = 0; j < 2; j++) {
			vector<int> out;
			textures[0]->getPixel(j,i, &out);
			cout << out[0] << ", " << out[1] << ", " << out[2] << ", " << out[3] << endl;
		}
	}*/
}

bool Material::hasTexture() const {
	return textures.size() > 0;
}

void Material::setAmbient(Vector3<double>  a) {
	Ka = a;
}
void Material::setDiffuse(Vector3<double>  a) {
	Kd = a;
}

void Material::setSpecular(Vector3<double> a) {
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
	final->push_back(round(Ka[0]*r));
	final->push_back(round(Ka[1]*g));
	final->push_back(round(Ka[2]*b));
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
//
// Comment starts here
//
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
	final->push_back(round(Kd[0]*r * abs(cos)));
	final->push_back(round(Kd[1]*g * abs(cos)));
	final->push_back(round(Kd[2]*b * abs(cos)));
	return final;
}

//vector<int> * Material::color_diffuse(const vector<int> * light_color, double cos, double x, double y) const {
//		
//	vector<int> * final = new vector<int>();
//	//final->push_back(round((*(*result)[0])[0] * abs(cos)));
//	//final->push_back(round((*(*result)[1])[0] * abs(cos)));
//	//final->push_back(round((*(*result)[2])[0] * abs(cos)));
////	cout << "r: " << (*light_color)[0] << " g: " << (*light_color)[1] << " b: " << (*light_color)[2] << endl;
//	//cout << "Kdg " << (*(*Kd)[index])[1] << endl;
//	double r,g,b;
//	r = (*light_color)[0];
//	g = (*light_color)[1];
//	b = (*light_color)[2];
//	vector<int> surfaceColor;
//	double w = textures[0]->getWidth();
//	double h = textures[0]->getHeight();
//	int x_pos = (w*x);
//	int y_pos = (h*y);
//	if (x_pos > 512 || y_pos > 512) {
////		cout << "OOB: " << x_pos << ", " << y_pos << endl;
//		return color_diffuse(light_color, cos);
//	}
//	textures[0]->getPixel(x_pos, y_pos, &surfaceColor);
//	
//	double sr, sg, sb;
//	
//	sr = (surfaceColor)[0]/255.0;
//	sg = (surfaceColor)[1]/255.0;
//	sb = (surfaceColor)[2]/255.0;
//	
////	cout << "cos: " << cos << endl;
//	
////	cout << "surface: " << sr << ", " << sg << ", " << sb << endl;
//
//	final->push_back(round(sr*r * abs(cos)));
//	final->push_back(round(sg*g * abs(cos)));
//	final->push_back(round(sb*b * abs(cos)));
//
////	cout << "color: "
////	<< (*final)[0] << ", "
////	<< (*final)[1] << ", "
////	<< (*final)[2] << endl;
//	
//	return final;
//}

vector<int> * Material::color_specular(const vector<int> * light_color, double cos) const {
	vector<int> * final = new vector<int>();
	double alpha = Ns;//[index];
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	//cout << "alpha: " << alpha << endl;
	final->push_back(round(Ks[0]*r * pow(cos, alpha)));
	final->push_back(round(Ks[1]*g * pow(cos, alpha)));
	final->push_back(round(Ks[2]*b * pow(cos, alpha)));
	return final;
}

vector<int> * Material::color_reflection(const vector<int> * light_color) const {
	vector<int> * final = new vector<int>();
	double r,g,b;
	r = (*light_color)[0];
	g = (*light_color)[1];
	b = (*light_color)[2];
	//cout << "alpha: " << alpha << endl;
	final->push_back(round(Ks[0]*r));
	final->push_back(round(Ks[1]*g));
	final->push_back(round(Ks[2]*b));
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
