#include "face.h"

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

Face::Face(const Material * mat) : normal(0,0,0) {
	//vertices;
	//vertex_numbers;
	material = mat;
}

Face::Face(const Face& a) : normal (0, 0, 0) {
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
	for (size_t i = 0; i < a.vertices.size(); i++) {
		Vector3<double> temp = a.vertices[i];
		vertices.push_back(temp);
	}
	//cout << "copied vertices" << endl;
	calculate_normal();
	return *this;
}

void Face::addVertex(Vector3<double> vert) {//, int index) {
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

void Face::addVertex(Vector3<double> vert, Vector3<double> * texVert) {
	int index = vertices.size();
	addVertex(vert);
	textureVertices[index] = texVert;
}

/*void Face::addTexVertex(Vertex vert) {
	textureVertices.push_back(vert);
}*/

/*
*    TODO Oh cry for the lost functionality! (Fix later...)
*
*
*/
/*
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
}*/

//std::vector<double> * Face::intersect(std::vector<double> * focal_point, std::vector<double> * view_point) {
Vector3<double> Face::intersect(const Vector3<double> focal_point, const Vector3<double> view_point, double *tee) const {
	Vector3<double> direction = Vector3<double>(
		view_point[0] - focal_point[0],
		view_point[1] - focal_point[1],
		view_point[2] - focal_point[2]);
	

	//cout << "VP magnitude: " << view_point->size() << endl;
	//cout << "view point: " << (*view_point)[0] << ", " << (*view_point)[1] << ", " << (*view_point)[2] << endl;

	
	
	Vector3<double> line = Vector3<double>(
		vertices[0][0] - focal_point[0],
		vertices[0][1] - focal_point[1],
		vertices[0][2] - focal_point[2]);
	
	//vector<double> * dir = normalize(direction);
	//vector<double> * ln = normalize(line);
	double T = line.dot(normal)/direction.dot(normal);
	*tee = T;
	//cout << T << " = " << dot_product(line, n) << "/" << dot_product(direction, n) << endl;
	// ((*focal_point)[0] - vertices[0].get_x())/((*direction)[0]);
	Vector3<double> p = Vector3<double>(
		focal_point[0] + (direction[0]*T),
		focal_point[1] + (direction[1]*T),
		focal_point[2] + (direction[2]*T));
		
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

bool Face::isInside(Vector3<double> & p) const {
	//cout << "p: " << (*p)[0] << ", " << (*p)[1] << ", " << (*p)[2] << endl;
	int index1;
	int index2;
	//const vector<double> * n = &normal;
	if (abs(normal[2]) > abs(normal[0]) && abs(normal[2]) > abs(normal[1])) {
		index1=0;
		index2=1;
	}
	else if (abs(normal[1]) > abs(normal[0])) {
		index1=0;
		index2=2;
	}
	else {
		index1=1;
		index2=2;
	}
	int count = 0;
	for (size_t i = 0; i < vertices.size(); i++) {
		int next = (i + 1) % vertices.size();
		//cout << "p: " << (*p)[0] << ", " << (*p)[1] << ", " << (*p)[2] << endl;
		
		vector<double> vertex1;
		vertex1.push_back(vertices[i][0]);
		vertex1.push_back(vertices[i][1]);
		vertex1.push_back(vertices[i][2]);
		//cout << "vertex1: " << vertex1[index1] << ", " << vertex1[index2] << endl;  

		vector<double> vertex2;
		vertex2.push_back(vertices[next][0]);
		vertex2.push_back(vertices[next][1]);
		vertex2.push_back(vertices[next][2]);
		//cout << "vertex2: " << vertex2[index1] << ", " << vertex2[index2] << endl;
		
		if (abs(vertex2[index2] - vertex1[index2]) > 0.000001) {
			double t = (p[index2] - vertex1[index2])/(vertex2[index2] - vertex1[index2]);	
		//	cout << t << " = (" << (*p)[index2] << " - " << vertex1[index2] << ")/(" << vertex2[index2] << " - " << vertex1[index2] << ")" << endl;
			double x = vertex1[index1] + t*(vertex2[index1] - vertex1[index1]);
		//	cout << x << " = " << vertex1[index1] << " + " << t << "*(" << vertex2[index1] << " - " << vertex1[index1] << ")" << endl;
		
			double max_y = max(vertex1[index2], vertex2[index2]);
			double min_y = min(vertex1[index2], vertex2[index2]);
			//cout << "index1: " << index1 << " index2: " << index2 << endl;
			//cout << "p_size: " << p->size() << endl;
		//	cout << "x:  " << x << " (*p)[index1] " << (*p)[index1] << " (*p)[index2] " << (*p)[index2] << " min_y " << min_y << " (*p)[index2] " << (*p)[index2] << " max_y " << max_y << endl;
			if (x > p[index1] && p[index2] > min_y && p[index2] <= max_y) {
				count++;
			}
		}
	}
	//cout << "count: " << count << endl;
	//n->~vector();
	return !(count % 2 == 0);
}

bool Face::calculate_normal() {
	Vector3<double> a = Vector3<double>(
		vertices[1][0] - vertices[0][0],
		vertices[1][1] - vertices[0][1],
		vertices[1][2] - vertices[0][2]);
	
	Vector3<double> b = Vector3<double>(
		vertices[2][0] - vertices[1][0],
		vertices[2][1] - vertices[1][1],
		vertices[2][2] - vertices[1][2]);
	
	Vector3<double> n = a.cross(b);
	
	//TODO fix this test
	if (abs(n[0]) < .00001 && abs(n[1]) < .00001 && abs(n[2]) < .00001) {
		//cerr << "First three points of face are linear!" << endl;
		//return false;
		//exit(1);
	}
	
	normal = n.normal();
	return true;
}

bool Face::test_coplanarity(Vector3<double> vert) {
	Vector3<double> a = Vector3<double>(
		vert[0] - vertices[0][0],
		vert[1] - vertices[0][1],
		vert[2] - vertices[0][2]);
	
	double test = a.dot(normal);//a[0]*(*normal)[0] + a[1]*(*normal)[1] + a[2]*(*normal)[2];

	if (abs(test) < .0001) {
		return true;
	}

	else return false;
}

const vector<Vector3<double>> & Face::getVertices() const{
	return vertices;
}

const Material * Face::get_material() const {
	return material;
}

const Vector3<double> * Face::getNormal() const{
	return &normal;
}

vector<int> * Face::colorDiffuse(const Vector3<double> point, const vector<int> * light_color, double cos) {
	 if (material->hasTexture()) {
                //cout << textureVertices.size() << endl;
                Vector3<double> first = Vector3<double> (
					vertices[0][0],
					vertices[0][1],
					vertices[0][2]);
				
                Vector3<double> second = Vector3<double> (
					vertices[1][0],
					vertices[1][1],
					vertices[1][2]);
				
                Vector3<double> third = Vector3<double>(
					vertices[2][0],
					vertices[2][1],
					vertices[2][2]);

                Vector3<double> one = first - second;
                Vector3<double> two = third - second;

                double lengthOne = one.magnitude();
                double lengthTwo = two.magnitude();

                //cout << (*one)[0] << ", " << (*one)[1] << ", " << (*one)[2] << endl;
                //cout << (*two)[0] << ", " << (*two)[1] << ", " << (*two)[2] << endl;

                Vector3<double> pointVector = point - second;

                double dotOne = one.normal().dot(pointVector);
                double dotTwo = two.normal().dot(pointVector);

 /*               Vector3<double> texOne = Vector3<double> (
					(*textureVertices[0])[0],
					(*textureVertices[0])[1],
					0);
				
                Vector3<double> texTwo = Vector3<double> (
					(*textureVertices[1])[0],
					(*textureVertices[1])[1],
					0);
						
                Vector3<double> texThree = Vector3<double> (
					(*textureVertices[2])[0],
					(*textureVertices[2])[1],
					0);
*/

                //if (textureVertices.count(1)) {

                //}
                //else return material->color_diffuse(light_color, cos);
                //if (textureVertices.count(2)) {

                //}
                //else return material->color_diffuse(light_color, cos);

                //Vector3<double> firstAxis = texOne - texTwo;
                //Vector3<double> secondAxis = texThree - texTwo;

                //double lengthAxisOne = firstAxis.magnitude();
                //double lengthAxisTwo = secondAxis.magnitude();

                double distOne = dotOne/lengthOne;
                double distTwo = dotTwo/lengthTwo;
//              cout << "success!! " << endl;

//              cout << "one: " << lengthOne << endl;
//              cout << "two: " << lengthTwo << endl;

//                return material->color_diffuse(light_color, cos, distOne, distTwo);
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
	for (size_t i = 0; i < face.vertices.size(); i++) {
		// TODO fix operator<< for Vector3
		//out << (face.vertices[i]) << " ";
	}
	return out << "\n";
}
