#ifndef GROUP_OBJECT_H
#define GROUP_OBJECT_H

#include "vertex.h"
#include "face.h"
#include "elipse.h"

#include <string>
#include <vector>

class Group {
	private:
		int start;
		std::string name;
		std::vector<Face *> faces;
		std::vector<Elipse *> elipses;
		std::vector<int> used_vertices;
		std::vector<Vertex> vertices;
	public:
		Group(std::string, int);
		Group(const Group&);
		~Group();
		std::ostream & operator<<(std::ostream &);
		Group& operator=(const Group&);
		
		std::string get_name();
		const std::vector<Face *> & get_faces();
		const std::vector<Elipse *> & get_elipses();
				
		void rotate(double, double, double, double);
		void arbitrary(std::vector<std::vector<double> *> *);
		void translate(double, double, double);
		void scale(double, double, double);
		void add_face(std::string, std::string, const std::vector<Vertex *> *, std::vector<Face *> *);
		void add_elipse(std::string, std::string, const std::vector<Vertex *> *, std::vector<Elipse *> *);
		void wipe(std::vector<Vertex *> *);
		int num_vertices();
		const std::vector<Vertex> * get_lines();
		friend std::ostream & operator<<(std::ostream &, const Group &);
	
};

std::ostream & operator<<(std::ostream &, const Group &);

#endif
