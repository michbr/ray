#ifndef FACE_OBJECT_H
#define FACE_OBJECT_H

#include "material.h"
#include "DragonMath/dragonmath.h"

#include <string>
#include <vector>
#include <unordered_map>


class Face {
	private:
		//std::vector<int> vertex_numbers;
		//std::vector<int> texVertNumbers;		

		std::vector<Vector3<double> > vertices;
		//std::vector<Vertex> textureVertices;

		std::unordered_map<int, Vector3<double> *> textureVertices;
		
		Vector3<double> normal;
		
		const Material * material;
		
		bool calculate_normal();
		bool test_coplanarity(Vector3<double>);
	public:
		Face(const Material * mat);
		Face(const Face&);
		Face& operator=(const Face&);
		
		void addVertex(Vector3<double>);//, int);
		void addVertex(Vector3<double>, Vector3<double> *);
		//void addTexVertex(Vertex);

		void rotate(double, double, double, double);
		void arbitrary(std::vector<std::vector<double> *> *);
		void translate(double, double, double);
		void scale(double, double, double);

		//std::vector<double> * intersect(std::vector<double> *, std::vector<double> *);  
		Vector3<double> intersect(const Vector3<double> , const Vector3<double> , double *) const;  
		bool isInside(Vector3<double> &) const;
		
		const std::vector<Vector3<double>> & getVertices() const;
		const Material * get_material() const;
		const Vector3<double> * getNormal() const;

		std::vector<int> * colorDiffuse(const Vector3<double> point, const std::vector<int> *, double);

		std::ostream & operator<<(std::ostream &);
		friend std::ostream & operator<<(std::ostream &, const Face &);
};

std::ostream & operator<<(std::ostream &, const Face &);

#endif
