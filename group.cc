#include "group.h"
#include "vertex.h"

#include <iostream>
#include <sstream>

using namespace std;

Group::Group(string group_name, int strt) {
	faces;
	vertices;
	used_vertices;
	name = group_name;
	start = strt;
}

Group::Group(const Group& a) {
	//cout << "copy constructor called..." << endl;
	faces;
	vertices;
	used_vertices;
	*this = a;

}

Group::~Group() {
	cout << "Group destructor called." << endl;
}

Group& Group::operator=(const Group& a) {
	//cout << "operator= called" << endl;	
	name = a.name;
	start = a.start;
	for (int i = 0; i < a.faces.size(); i++) {
		Face * temp = new Face(*a.faces[i]);
		faces.push_back(temp);
	}
	//cout << "copied faces" << endl;
	for (int i = 0; i < a.used_vertices.size(); i++) {
		used_vertices.push_back( a.used_vertices[i]);
	}
	//cout << "copied used_vertices group" << endl;
	for (int i = 0; i < a.vertices.size(); i++) {
		Vertex temp = a.vertices[i];
		vertices.push_back(temp);
	}
	//cout << "copied vertices groups" << endl;
	return *this;
	
}

string Group::get_name() {
	return name;
}

const vector<Face *> & Group::get_faces() {
	return faces;
}

const vector<Elipse *> & Group::get_elipses() {
	return elipses;
}

void Group::rotate(double amount, double x_val, double y_val, double z_val) {
	for (int i = 0; i < faces.size(); i++) {
		faces[i]->rotate(amount, x_val, y_val, z_val);
	}
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].rotate(amount, x_val, y_val, z_val);
	}
}

void Group::arbitrary(vector<vector<double> *> * arb) {
	for (int i = 0; i < faces.size(); i++) {
		faces[i]->arbitrary(arb);
	}
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].arbitrary(arb);
	}

}

void Group::translate(double x_val, double y_val, double z_val) {
	for (int i = 0; i < faces.size(); i++) {
		faces[i]->translate(x_val, y_val, z_val);
	}
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].translate(x_val, y_val, z_val);
	}

}

void Group::scale(double x_val, double y_val, double z_val) {
	for (int i = 0; i < faces.size(); i++) {
		faces[i]->scale(x_val, y_val, z_val);
	}
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].scale(x_val, y_val, z_val);;
	}
	
}

void Group::add_face(string line, string material, const vector<Vertex *> * vertexes, vector<Face *> * face_list) {
	stringstream s;
	string trash;
	s << line;
	s >> trash;
	int num;
	int num_vertices = 0;
	Face * face = new Face(material);
		while (s.good()){
			s >> num;
			if (!s.fail()) {
				bool used = false;
				int index;
				for (int i = 0; i < used_vertices.size(); i++) {
					if ((num - 1) == used_vertices[i]) {
						index = i;
						used = true;
					}
				}
				if ((*vertexes)[num-1] == NULL) {
					cerr << "Vertices can only be used in one group!" << endl;
					exit(1);
				}
				if (used) {
					face->add_vertex((*(*vertexes)[num-1]), index + start);
					num_vertices++;
				}
				else {
					vertices.push_back((*(*vertexes)[num-1]));
					used_vertices.push_back(num - 1);
					face->add_vertex((*(*vertexes)[num-1]), (vertices.size()-1) + start);
					num_vertices++;
				}
			}
		}
		if (num_vertices < 3) {
			cerr << "Faces must contain at least 3 vertices.\n";
			exit(1);
		}
		face_list->push_back(face);
		faces.push_back(face);
}

void Group::add_elipse(string line, string material, const vector<Vertex *> * vertexes, vector<Elipse *> * elipse_list) {
	stringstream s;
	string trash;
	int vertex_num;
	double x,y,z;
	s << line;
	s >> trash >> vertex_num >> x >> y >> z;

	bool used = false;
	int index;
	for (int i = 0; i < used_vertices.size(); i++) {
		if ((vertex_num - 1) == used_vertices[i]) {
			index = i;
			used = true;
		}
	}
	if ((*vertexes)[vertex_num-1] == NULL) {
		cerr << "Vertices can only be used in one group!" << endl;
		exit(1);
	}
	if (used) {
		//elipse.add_vertex((*(*vertexes)[vertex_num-1]), index + start);
		//Elipse elipse((*(*vertexes)[vertex_num-1]).get_x(), (*(*vertexes)[vertex_num-1]).get_y(), (*(*vertexes)[vertex_num-1]).get_z(), (*(*vertexes)[vertex_num-1]).get_w(), x,y,z);
		Elipse* elipse = new Elipse(material, (*(*vertexes)[vertex_num-1]), x,y,z);
		elipses.push_back(elipse);
		elipse_list->push_back(elipse);
	}
	else {
		vertices.push_back((*(*vertexes)[vertex_num-1]));
		used_vertices.push_back(vertex_num - 1);
		Elipse * elipse = new Elipse(material, (*(*vertexes)[vertex_num-1]), x,y,z);
		//Elipse elipse((*(*vertexes)[vertex_num-1]).get_x(), (*(*vertexes)[vertex_num-1]).get_y(), (*(*vertexes)[vertex_num-1]).get_z(), (*(*vertexes)[vertex_num-1]).get_w(), x,y,z);
		elipses.push_back(elipse);
		elipse_list->push_back(elipse);
		//elipse.add_vertex((*(*vertexes)[vertex_num-1]), (vertices.size()-1) + start);
	}
}

void Group::wipe(std::vector<Vertex *> * vertexes) {
	for (int i = 0; i < used_vertices.size(); i++) {
		(*vertexes)[used_vertices[i]] = NULL;
	}
}

int Group::num_vertices() {
	return vertices.size();
}

const vector<Vertex> * Group::get_lines(){
	vector<Vertex> * lines = new vector<Vertex>();
	for (int i = 0; i < faces.size(); i++) {
		
		const vector<Vertex> * face = faces[i]->get_vertices();
		for(int j = 0; j < face->size()-1; j++) {
			lines->push_back((*face)[j]);
			lines->push_back((*face)[j+1]);
		}
		lines->push_back((*face)[face->size() - 1]);
		lines->push_back((*face)[0]);
	}
	return lines;
}

ostream & Group::operator<<(ostream & out) {
	if (name != "default") {
		out << "g " << name << "\n";
	}
	
	for (int i = 0; i < vertices.size(); i++) {
		out << vertices[i];
	}
	out << '\n';

	for (int i = 0; i < faces.size(); i++) {
		out << *(faces[i]);
	}
	return out;
}

std::ostream & operator<<(std::ostream & out, const Group & group) {
	if (group.name != "default") {
		out << "g " << group.name << "\n";
	}
	for (int i = 0; i < group.vertices.size(); i++) {
		out << group.vertices[i];
	}
	out << '\n';

	for (int i = 0; i < group.faces.size(); i++) {
		out << *(group.faces[i]);
	}
	return out;
}
