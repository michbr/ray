#ifndef FACE_OBJECT_H
#define FACE_OBJECT_H

#include "vertex.h"
#include "material.h"

#include <string>
#include <vector>
#include <unordered_map>


class Face {
	private:
		//std::vector<int> vertex_numbers;
		//std::vector<int> texVertNumbers;		

		std::vector<Vertex> vertices;
		//std::vector<Vertex> textureVertices;

		std::unordered_map<int, Vertex *> textureVertices;
		
		std::vector<double> normal;
		
		const Material * material;
		
		bool calculate_normal();
		bool test_coplanarity(Vertex);
	public:
		Face(const Material * mat);
		Face(const Face&);
		Face& operator=(const Face&);
		
		void add_vertex(Vertex);//, int);
		void add_vertex(Vertex, Vertex *);
		//void addTexVertex(Vertex);

		void rotate(double, double, double, double);
		void arbitrary(std::vector<std::vector<double> *> *);
		void translate(double, double, double);
		void scale(double, double, double);

		//std::vector<double> * intersect(std::vector<double> *, std::vector<double> *);  
		std::vector<double> * intersect(const std::vector<double> *, const std::vector<double> *, double *) const;  
		bool is_inside(std::vector<double> *) const;
		
		const std::vector<Vertex> * get_vertices() const;
		const Material * get_material() const;
		const std::vector<double> * get_normal() const;

		std::vector<int> * color_diffuse(const std::vector<double> * point, const std::vector<int> *, double);

		std::ostream & operator<<(std::ostream &);
		friend std::ostream & operator<<(std::ostream &, const Face &);
};

std::ostream & operator<<(std::ostream &, const Face &);

#endif
