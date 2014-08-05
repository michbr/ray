#include "reader.h"
#include "vertex.h"
#include "face.h"
#include "group.h"
#include "wireframe.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Reader::Reader() {
	//vertices;
	//used_vertices;
	//groups;
	//cameras;
	//lights.push_back(new Light(0, 0, 0, 0, 60, 60, 60)); //Ambient light
	lights.push_back(new Light(0, 0, 0, 0, 0, 0, 0)); //Ambient light
	current_group =  new Group("default", 0);
	groups.push_back(current_group);
}

void Reader::tokenize (string line) {
	string token = line;
	while (token[0] < 33 && token.length() > 1) { //strip off all the leading whitespace(and any other crap)
		token = token.substr( 1, (token.length() - 1) );
	}
	if (token.length() < 2) {
		return;
	}

	if (token[0] == 'v') {
		Vertex * vert = new Vertex(line);
		cout << "Adding Vertex:\n\t" << *vert << endl;
		vertices.push_back(vert);
	}
	
	else if (token[0] == 'f') {
		current_group->add_face(line, current_material, &vertices, &faces);
		cout << "Adding face." << endl;
	}
	else if (token[0] == 'g'){
		stringstream s;
		string trash;
		string name;
		s << line;
		s >> trash >> name;
		current_group->wipe(&vertices);
		Group * temp = new Group(name, current_group->num_vertices());
		current_group = temp;
		groups.push_back(current_group);
		cout << "Adding group:\n\t" << name << endl;
	}
	
	else if (token[0] == 'r') {
		stringstream s;
		string trash;
		string name;
		double amount,x,y,z;
		s << line;
		s >> trash;
		s >> name;
		if (!s.good()) {
			cerr << "Must include group name!" << endl;
			exit(1);
		}
		s >> amount >> x >> y;
		if (!s.good()) {
			cerr << "Not enough arguments!" << endl;
			exit(1);
		}
		s >> z;
		bool found = false;
		for (int i = 0; i < groups.size(); i++) {
			if (groups[i]->get_name().compare(name) == 0) {
				groups[i]->rotate(amount, x, y, z);
				found = true;
			}
		}
		if (!found) {
			cerr << "Specified group does not exist!" << endl;
			exit(1);
		}
	}
	
	else if (token[0] == 't') {
		stringstream s;
		string trash;
		string name;
		double x,y,z;
		s << line;
		s >> trash;
		s >> name;
		if (!s.good()) {
			cerr << "Must include group name!" << endl;
			exit(1);
		}
		s >> x >> y;
		if (!s.good()) {
			cerr << "Not enough arguments!" << endl;
			exit(1);
		}
		s >> z;
		bool found = false;
		for (int i = 0; i < groups.size(); i++) {
			if (groups[i]->get_name().compare(name) == 0) {
				groups[i]->translate(x, y, z);
				found = true;
			}
		}
		if (!found) {
			cerr << "Specified group does not exist!" << endl;
			exit(1);
		}
	}
	
	else if (token[0] == 's') {
		stringstream s;
		string trash;
		string name;
		double x,y,z;
		s << line;
		s >> trash; 
		s >> name;
		if (!s.good()) {
			cerr << "Must include group name!" << endl;
			exit(1);
		}
		s >> x >> y;
		if (!s.good()) {
			cerr << "Not enough arguments!" << endl;
			exit(1);
		}
		s >> z;
		bool found = false;
		for (int i = 0; i < groups.size(); i++) {
			if (groups[i]->get_name().compare(name) == 0) {
				groups[i]->scale(x, y, z);
				found = true;
			}
		}
		if (!found) {
			cerr << "Specified group does not exist!" << endl;
			exit(1);
		}
	}
	
	else if (token[0] == 'a') {
		stringstream s;
		string trash;
		string name;
		vector<vector<double> *> * arb = new vector<vector<double>*>();
		s << line;
		s >> trash;
		s >> name;
		if (!s.good()) {
			cerr << "Must include group name!" << endl;
			exit(1);
		}
		vector<double> * row1 = new vector<double>();
		vector<double> * row2 = new vector<double>();
		vector<double> * row3 = new vector<double>();
		vector<double> * row4 = new vector<double>();
		
		double x,y,z,w;
		s >> x >> y >> z >> w;
		row1->push_back(x);
		row1->push_back(y);
		row1->push_back(z);
		row1->push_back(w);
 
		s >> x >>y >>z >>w;
		row2->push_back(x);
		row2->push_back(y);
		row2->push_back(z);
		row2->push_back(w);
		s >> x >>y >>z >>w;
		row3->push_back(x);
		row3->push_back(y);
		row3->push_back(z);
		row3->push_back(w);
		s >> x >>y >>z;
		if (!s.good()) {
			cerr << "Not enough arguments!" << endl;
			exit(1);
		}
		s >>w;
		row4->push_back(x);
		row4->push_back(y);
		row4->push_back(z);
		row4->push_back(w);
		
		arb->push_back(row1);
		arb->push_back(row2);
		arb->push_back(row3);
		arb->push_back(row4);
		
		bool found = false;
		for (int i = 0; i < groups.size(); i++) {
			if (groups[i]->get_name().compare(name) == 0) {
				groups[i]->arbitrary(arb);
				found = true;
			}
		}
		if (!found) {
			cerr << "Specified group does not exist!" << endl;
			exit(1);
		}
	}

	else if (token[0] == 'c') { //read in a camera
		stringstream s;
		string trash;
		string name;
		s << token;
		s >> trash >> name;
		vector<double> arguments;
		while (s.good()) {
			double temp;
			s >> temp;
			arguments.push_back(temp);
		}
		if (arguments.size() != 10) {
			cerr << "Not enough arguments to create camera: " << name << endl;
			exit(1);
		}
		vector<double> * vpn = new vector<double>();
		vector<double> * vup = new vector<double>();

		vpn->push_back(arguments[4]);
		vpn->push_back(arguments[5]);
		vpn->push_back(arguments[6]);
	
		vup->push_back(arguments[7]);
		vup->push_back(arguments[8]);
		vup->push_back(arguments[9]);
		cameras.push_back(new Camera(name, arguments[0], arguments[1], arguments[2], arguments[3], vpn, vup));
		cout << "Adding camera." << endl;
	}

	else if (token[0] == 'w') { //read in a wire frame?
		stringstream s;
		string trash;
		string name;
		s << token;
		s >> trash >> name;
		vector<double> arguments;
		while (s.good()) {
			double temp;
			s >> temp;
			arguments.push_back(temp);
		}
		if (arguments.size() != 4) {
			cerr << "Not enough arguments to create wire-frame for: " << name << endl;
			exit(1);
		}
		for (int i = 0; i < cameras.size(); i++) {
			if (cameras[i]->get_name().compare(name) == 0) {
				cameras[i]->add_frame(new Wireframe(name, arguments[0], arguments[1], arguments[2], arguments[3], 1));
			}
		}
	}
	
	else if (token[0] == 'e') {
		current_group->add_elipse(line, current_material, &vertices, &elipses);
		
	}
	else if (token[0] == 'l' ) {
		//added all this
		stringstream s;
		s << line;
		string trash;
		double x,y,z,w;
		int r,g,b;
		s >> trash >> x >> y >> z >> w >> r >> g >> b;
		//if (s.good()) {

		Light * l = new Light(x, y, z, w, r, g, b);
		lights.push_back(l);
		//}
		cout << "Adding light." << endl;
 	}
	else if (token[0] == 'q') {
		stringstream s;
		s << line;
		string trash, name;
		double height, width;
		int depth;
		s >> trash >> name >> width >> height >> depth;
		for (int i = 0; i < cameras.size(); i++) {
			cameras[i]->add_frame(new Wireframe(name, -(width/2), -(height/2), width/2, height/2, depth));
		}
		//cout << "pushing back: "  << name << endl;
		files.push_back(name);
	}
	else if (token[0] == 'm') {
		stringstream s;
		s << line;
		string trash, name;
		s >> trash >> name;
		if (trash.compare("mtllib") == 0) {
			materials.load_materials(name);
		}
	}
	else if (token[0] == 'u') {
		stringstream s;
		s << line;
		string trash, name;
		s >> trash >> name;
		if (trash.compare("usemtl") == 0) {
			current_material = name;
		}
	}
}

void Reader::read (string file_name) {

	ifstream input;
	input.open (file_name.c_str());
	string line;
	
	while(input.good()) {
		char temp;
		temp = (char) input.get(); //get a new character
		while (!( (temp > 47 && temp < 58) || (temp > 64 && temp < 91) || (temp > 96 && temp < 123) || temp == '\n' || temp == '#' || temp == '.' || temp == 32 || temp == '-') && input.good()) {
			temp = (char) input.get(); //get a new character
		}
		if (temp == '\n') {
			if (!line.empty()) {
				tokenize(line);
				line = "";
			}
		}
		else if (temp == '#') { //if you encounter a '#', throw away the rest of the line
			if (!line.empty() && line.compare("\n") != 0){
				tokenize(line);
			}
			line = "";
			while (input.good() && input.get() != '\n') {
			}
		}
		else {
			if (!input.good() && !line.empty()) {
				tokenize(line);
			}
			line += temp;
		}
	}
	
	input.close();
}

void Reader::write (string file_name) {
	ofstream output;
	output.open(file_name.c_str());
	for (int i = 0; i < groups.size(); i++) {
		output << *(groups[i]); 
	}
	output.close();
}

void Reader::wireframe (string file_name) {
	string file;
	for (int i = 0; i < cameras.size(); i++) {
		if (cameras[i]->hasFrame()) {
			
			vector<Group *> copy = vector<Group *>();
			for (int j = 0; j < groups.size(); j++) {
				Group * temp = new Group(*(groups[j]));
				copy.push_back(temp);
			}
			cameras[i]->prepare_wireframe(copy);
			//cameras[i]->prepare_raycast(copy);
			ofstream output;
			//cout << cameras.size() << endl;
			if (cameras.size() > 1) {
				stringstream s;
				int period = file_name.find_first_of(".");
				s << file_name.substr(0, period);
				if (i < 9) {
					s << "0" << i+1;
				}
				else {
					s << i + 1;
				}
				s << file_name.substr(period, file_name.length());
				s >> file;
			}
			else {
				file = file_name;
			}
			output.open(file.c_str());
			output << *(cameras[i]);
			output.close();
		}
	}
}

void Reader::raycast () {
	string file = files[0];
	for (int i = 0; i < cameras.size(); i++) {
		if (cameras[i]->hasFrame()) {
			
			//vector<Group *> copy = vector<Group *>();
			//for (int j = 0; j < groups.size(); j++) {
			//	Group * temp = new Group(*(groups[j]));
			//	copy.push_back(temp);
			//}
			//cameras[i]->prepare_wireframe(copy);
			cameras[i]->prepare_raycast(faces, elipses, lights, materials);
			ofstream output;
			//cout << cameras.size() << endl;
			//if (cameras.size() > 1) {
			//	stringstream s;
				//int period = file_name.find_first_of(".");
				//s << file_name.substr(0, period);
				//if (i < 9) {
				//	s << "0" << i+1;
				//}
				//else {
			//		s << i + 1;
			//	}
			//	s << file_name.substr(period, file_name.length());
			//	s >> file;
			//}
			//else {
			//	file = file_name;
			//}
			stringstream s;
			s << file;
			s << ".ppm";
			string file_name;
			s >> file_name;
		//	cout << "file name: " << file_name << endl;
			output.open(file_name.c_str());
			output << *(cameras[i]);
			output.close();
		}
	}
}

int main (int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " model commands\n";
		exit(1);
	}
	Reader test;
	
	test.read(argv[1]);
	test.read(argv[2]);
	test.raycast();
	//test.write(argv[3]);
	
	return 0;
}
