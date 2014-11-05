#include "face.h"
#include "MatMath.h"

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

Face::Face(const Material * mat) {
	//vertices;
	//vertex_numbers;
	material = mat;
}

Face::Face(const Face& a) {
	vertices;
	//vertex_numbers;
	cout << "face copy called" << endl;
	*this = a;
}

Face& Face::operator=(const Face& a) {
	cout << "face = called" << endl;
	material = a.material;
	//for (int i = 0; i < a.vertex_numbers.size(); i++) {
	//	vertex_numbers.push_back(a.vertex_numbers[i]);
	//}
	//cout << "copied vertex_numbers" << endl;
	for (int i = 0; i < a.vertices.size(); i++) {
		Vertex temp = a.vertices[i];
		vertices.push_back(temp);
	}
	//cout << "copied vertices" << endl;
	calculate_normal();
	return *this;
}

void Face::add_vertex(Vertex vert) {//, int index) {
	if (vertices.size() >= 3) {
		if (!test_coplanarity(vert)) {
			cerr << "Face contains significantly non co-planar vertices!\n";
			exit(1);
		}
	}
	vertices.push_back(vert);
	//vertex_numbers.push_back(index);
	if (vertices.size() == 3) {
		calculate_normal();
	}
}

void Face::add_vertex(Vertex vert, Vertex * texVert) {
	int index = vertices.size();
	add_vertex(vert);
	textureVertices[index] = texVert;
}

/*void Face::addTexVertex(Vertex vert) {
	textureVertices.push_back(vert);
}*/

void Face::rotate(double amount, double x_val, double y_val, double z_val) {
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i].rotate(amount, x_val, y_val, z_val);
	}
}

void Face::arbitrary(vector<vector<double> *> * arb) {
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i].arbitrary(arb);
	}
}

void Face::translate(double x_val, double y_val, double z_val) {
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i].translate(x_val, y_val, z_val);
	}
}

void Face::scale(double x_val, double y_val, double z_val) {
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i].scale(x_val, y_val, z_val);
	}
}

//std::vector<double> * Face::intersect(std::vector<double> * focal_point, std::vector<double> * view_point) {
std::vector<double> * Face::intersect(const vector<double> * focal_point, const vector<double> * view_point, double *tee) const {
	vector<double> direction;// = new vector<double>();
	vector<double> * p = new vector<double>();
	//cout << "VP length: " << view_point->size() << endl;
	//cout << "view point: " << (*view_point)[0] << ", " << (*view_point)[1] << ", " << (*view_point)[2] << endl;
	direction.push_back((*view_point)[0] - (*focal_point)[0]);
	direction.push_back((*view_point)[1] - (*focal_point)[1]);
	direction.push_back((*view_point)[2] - (*focal_point)[2]);
	
	
	vector<double> line;// = new vector<double>();
	line.push_back(vertices[0].get_x() - (*focal_point)[0]);
	line.push_back(vertices[0].get_y() - (*focal_point)[1]);
	line.push_back(vertices[0].get_z() - (*focal_point)[2]);
	
	const vector<double> * n = &normal;
	//vector<double> * dir = normalize(direction);
	//vector<double> * ln = normalize(line);
	
	double T = dot_product(&line, n)/dot_product(&direction, n);
	*tee = T;
	//cout << T << " = " << dot_product(line, n) << "/" << dot_product(direction, n) << endl;
	// ((*focal_point)[0] - vertices[0].get_x())/((*direction)[0]);

	p->push_back((*focal_point)[0] + (direction[0]*T) );
	p->push_back((*focal_point)[1] + (direction[1]*T) );
	p->push_back((*focal_point)[2] + (direction[2]*T) );
	
	//cout << "p: " << (*p)[0] << ", " << (*p)[1] << ", " << (*p)[2] << endl;
	
	
	/*double min = (*n)[0];
	int index;
	for (int i = 1; i < 3; i++) {
		if ((*n)[i] < min) {
			index = i;
			min = (*n)[i];
		}
	}
	
	vector<double> * m = make_perpendicular(n);
	vector<double> * u = cross_product(n, m);
	u = normalize(u);
	*/
	//n->~vector();
	return p;
	//return is_inside(&p);//results;
	//return true;
}

bool Face::is_inside(vector<double> * p) const {
	//cout << "p: " << (*p)[0] << ", " << (*p)[1] << ", " << (*p)[2] << endl;
	int index1;
	int index2;
	const vector<double> * n = &normal;
	if (abs((*n)[2]) > abs((*n)[0]) && abs((*n)[2]) > abs((*n)[1])) {
		index1=0;
		index2=1;
	}
	else if (abs((*n)[1]) > abs((*n)[0])) {
		index1=0;
		index2=2;
	}
	else {
		index1=1;
		index2=2;
	}
	int count = 0;
	for (int i = 0; i < vertices.size(); i++) {
		int next = (i + 1) % vertices.size();

		//cout << "p: " << (*p)[0] << ", " << (*p)[1] << ", " << (*p)[2] << endl;
		
		vector<double> vertex1;
		vertex1.push_back(vertices[i].get_x());
		vertex1.push_back(vertices[i].get_y());
		vertex1.push_back(vertices[i].get_z());
		//cout << "vertex1: " << vertex1[index1] << ", " << vertex1[index2] << endl;  

		vector<double> vertex2;
		vertex2.push_back(vertices[next].get_x());
		vertex2.push_back(vertices[next].get_y());
		vertex2.push_back(vertices[next].get_z());
		//cout << "vertex2: " << vertex2[index1] << ", " << vertex2[index2] << endl;
		
		if (abs(vertex2[index2] - vertex1[index2]) > 0.000001) {
			double t = ((*p)[index2] - vertex1[index2])/(vertex2[index2] - vertex1[index2]);	
		//	cout << t << " = (" << (*p)[index2] << " - " << vertex1[index2] << ")/(" << vertex2[index2] << " - " << vertex1[index2] << ")" << endl;
			double x = vertex1[index1] + t*(vertex2[index1] - vertex1[index1]);
		//	cout << x << " = " << vertex1[index1] << " + " << t << "*(" << vertex2[index1] << " - " << vertex1[index1] << ")" << endl;
		
			double max_y = max(vertex1[index2], vertex2[index2]);
			double min_y = min(vertex1[index2], vertex2[index2]);
			//cout << "index1: " << index1 << " index2: " << index2 << endl;
			//cout << "p_size: " << p->size() << endl;
		//	cout << "x:  " << x << " (*p)[index1] " << (*p)[index1] << " (*p)[index2] " << (*p)[index2] << " min_y " << min_y << " (*p)[index2] " << (*p)[index2] << " max_y " << max_y << endl;
			if (x > (*p)[index1] && (*p)[index2] > min_y && (*p)[index2] <= max_y) {
				count++;
			}
		}
	}
	//cout << "count: " << count << endl;
	//n->~vector();
	return !(count % 2 == 0);
}

bool Face::calculate_normal() {
	vector<double> a;
	vector<double> b;
	a.push_back(vertices[1].get_x() - vertices[0].get_x());
	a.push_back(vertices[1].get_y() - vertices[0].get_y());
	a.push_back(vertices[1].get_z() - vertices[0].get_z());
	
	b.push_back(vertices[2].get_x() - vertices[1].get_x());
	b.push_back(vertices[2].get_y() - vertices[1].get_y());
	b.push_back(vertices[2].get_z() - vertices[1].get_z());
	vector<double> * n = cross_product(&a, &b);
	if (abs((*n)[0]) < .00001 && abs((*n)[1]) < .00001 && abs((*n)[2]) < .00001) {
		//cerr << "First three points of face are linear!" << endl;
		//return false;
		//exit(1);
	}
	n = normalize(n);
	normal.push_back((*n)[0]);
	normal.push_back((*n)[1]);
	normal.push_back((*n)[2]);
	n->~vector();
	return true;
}

bool Face::test_coplanarity(Vertex vert) {
	vector<double> * a = new vector<double>();
	a->push_back(vert.get_x() - vertices[0].get_x());
	a->push_back(vert.get_y() - vertices[0].get_y());
	a->push_back(vert.get_z() - vertices[0].get_z());
	
	double test = dot_product(a, &normal);//a[0]*(*normal)[0] + a[1]*(*normal)[1] + a[2]*(*normal)[2];
	a->clear();
	a->~vector();
	if (abs(test) < .0001) {
		return true;
	}

	else return false;
}

const vector<Vertex> * Face::get_vertices() const{
	return & vertices;
}

const Material * Face::get_material() const {
	return material;
}

const std::vector<double> * Face::get_normal() const{
	return &normal;
}

vector<int> * Face::color_diffuse(const std::vector<double> * point, const std::vector<int> * light_color, double cos) {
	 if (material->hasTexture()) {
                //cout << textureVertices.size() << endl;
                vector<double> first;
                vector<double> second;
                vector<double> third;

                first.push_back(vertices[0].get_x());
                first.push_back(vertices[0].get_y());
                first.push_back(vertices[0].get_z());

                second.push_back(vertices[1].get_x());
                second.push_back(vertices[1].get_y());
                second.push_back(vertices[1].get_z());

                third.push_back(vertices[2].get_x()); 
                third.push_back(vertices[2].get_y());
                third.push_back(vertices[2].get_z());

                vector<double> * one = subtract(&first, &second);
                vector<double> * two = subtract(&third, &second);

                double lengthOne = magnitude(one);
                double lengthTwo = magnitude(two);

                //cout << (*one)[0] << ", " << (*one)[1] << ", " << (*one)[2] << endl;
                //cout << (*two)[0] << ", " << (*two)[1] << ", " << (*two)[2] << endl;

                vector<double> * pointVector = subtract(point, &second);

                double dotOne = dot_product(normalize(one), pointVector);
                double dotTwo = dot_product(normalize(two), pointVector);

                vector<double> texOne;
                vector<double> texTwo;
                vector<double> texThree;

        //      const Vertex * o = textureVertices[0];

                texOne.push_back(textureVertices[0]->get_x());
                texOne.push_back(textureVertices[0]->get_y());
                texOne.push_back(0);
                //if (textureVertices.count(1)) {
                        texTwo.push_back(textureVertices[1]->get_x());
                        texTwo.push_back(textureVertices[1]->get_y());
                        texTwo.push_back(0);
                //}
                //else return material->color_diffuse(light_color, cos);
                //if (textureVertices.count(2)) {
                        texThree.push_back(textureVertices[2]->get_x());
                        texThree.push_back(textureVertices[2]->get_y());
                        texThree.push_back(0);
                //}
                //else return material->color_diffuse(light_color, cos);

                vector<double> * firstAxis = subtract(&texOne, &texTwo);
                vector<double> * secondAxis = subtract(&texThree, &texTwo);

                double lengthAxisOne = magnitude(firstAxis);
                double lengthAxisTwo = magnitude(secondAxis);

                double distOne = dotOne/lengthOne;
                double distTwo = dotTwo/lengthTwo;
//              cout << "success!! " << endl;

//              cout << "one: " << lengthOne << endl;
//              cout << "two: " << lengthTwo << endl;

                return material->color_diffuse(light_color, cos, distOne, distTwo);
                //vector<double> * pointVector2 = subtract(
                //double AxisOneDot = dot_product(first,Axis

        }

        return material->color_diffuse(light_color, cos);


}

ostream & Face::operator<<(ostream & out) {
	out << "f ";
	//for (int i = 0; i < vertex_numbers.size(); i++) {
	//	out << (vertex_numbers[i] + 1) << " ";
	//}
	return out << "\n";
}

std::ostream & operator<<(std::ostream & out, const Face & face) {
	out << "f ";
	//for (int i = 0; i < face.vertices.size(); i++) {
	//	out << (face.vertex_numbers[i] + 1) << " ";
	//}
	return out << "\n";
}
