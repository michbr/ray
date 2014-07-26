#ifndef FACE_OBJECT_H
#define FACE_OBJECT_H

#include "vertex.h"

#include <string>
#include <vector>

class Face {
	private:
		std::vector<int> vertex_numbers;
		std::vector<Vertex> vertices;
		std::vector<double> normal;
		
		std::string material;
		
		void calculate_normal();
		bool test_coplanarity(Vertex);
	public:
		Face(std::string);
		Face(const Face&);
		~Face();
		Face& operator=(const Face&);
		
		void add_vertex(Vertex, int);

		void rotate(double, double, double, double);
		void arbitrary(std::vector<std::vector<double> *> *);
		void translate(double, double, double);
		void scale(double, double, double);

		//std::vector<double> * intersect(std::vector<double> *, std::vector<double> *);  
		std::vector<double> * intersect(const std::vector<double> *, const std::vector<double> *, double *) const;  
		bool is_inside(std::vector<double> *) const;
		
		const std::vector<Vertex> * get_vertices() const;
		std::string get_material() const;
		const std::vector<double> * get_normal() const;

		std::ostream & operator<<(std::ostream &);
		friend std::ostream & operator<<(std::ostream &, const Face &);
};

std::ostream & operator<<(std::ostream &, const Face &);

#endif
