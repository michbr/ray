
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_MESH_H
#define RAY_MESH_H

#include "math.h"
#include "shape.h"

#include <iostream>
#include <vector>


class Mesh;

class TriangleGroup {
	public:
		std::vector<unsigned short> indices;
		std::vector<Vector3<double>> surfNormals;
		std::vector<unsigned short> materials;
		
		void addTriangle(unsigned short ia, unsigned short ib, unsigned short ic, unsigned short material, const Mesh &parent);
		void shrinkToFit();
		unsigned int triangleCount() const;
		
		// must be normalized ray
		bool intersects(const Ray3<double> &ray, const Mesh &parent) const;
		double intersection(const Ray3<double> &ray, const Mesh &parent) const;
		Collision collision(const Ray3<double> &ray, const Mesh &parent) const;
};


class Mesh: public Shape {
    public:
		std::vector<Vector4<double>> vertices;
		std::vector<Vector3<double>> vertNormals;
		std::vector<TriangleGroup> groups;

		Mesh();
		Mesh(const Mesh &source);
		
		void addTriangle(unsigned short ia, unsigned short ib, unsigned short ic, unsigned short material);
		void calcVertNormals();
		void shrinkToFit();

		// must be normalized ray
		bool intersects(const Ray3<double> &ray) const;
		double intersection(const Ray3<double> &ray) const;
		Collision collision(const Ray3<double> &ray) const;
};

std::ostream &operator<<(std::ostream &out, const Mesh &mesh);

#endif // RAY_MESH_H
