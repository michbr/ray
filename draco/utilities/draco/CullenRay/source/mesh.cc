
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../mesh.h"

#include <cmath>
#include <cfloat>

using namespace std;


//////////
// Mesh //
//////////

Mesh::Mesh() {}
Mesh::Mesh(const Mesh &source): vertices(source.vertices), groups(source.groups) {}

bool Mesh::intersects(const Ray3 &ray) const {
	for(unsigned int i=0; i<groups.size(); ++i) {
		if (groups[i].intersects(ray, *this))
			return true;
	}
	return false;
}

double Mesh::intersection(const Ray3 &ray) const {
	double min = DBL_MAX;
	for(size_t i=0; i<groups.size(); ++i) {
		double newMin = groups[i].intersection(ray, *this);
		if (newMin < min && newMin >= 0) {
			min = newMin;
		}
	}
	return min;
}

Collision Mesh::collision(const Ray3 &ray) const {
	Collision min;
	for(size_t i=0; i<groups.size(); ++i) {
		Collision newMin = groups[i].collision(ray, *this);
		if (newMin.distance < min.distance && newMin.distance >= 0) {
			min = newMin;
		}
	}
	min.shape = this;
	return min;
}

void Mesh::addTriangle(unsigned short a, unsigned short b, unsigned short c, unsigned short material) {
	if (groups.size() < 1)
		groups.push_back(TriangleGroup());
	groups.back().addTriangle(a, b, c, material, *this);
}

void Mesh::calcVertNormals() {
	vertNormals.clear();
	vertNormals.resize(vertices.size());
	for(size_t i=0; i<groups.size(); ++i) {
		const TriangleGroup &group = groups[i];
		for(size_t j=0; j<group.surfNormals.size(); ++j) {
			size_t k = j *3;
			vertNormals[group.indices[k  ]] += group.surfNormals[j];
			vertNormals[group.indices[k+1]] += group.surfNormals[j];
			vertNormals[group.indices[k+2]] += group.surfNormals[j];
		}
    }
	for(size_t i=0; i<vertNormals.size(); ++i) {
		vertNormals[i].normalize();
	}
}

void Mesh::shrinkToFit() {
	for(unsigned int i=0; i<groups.size(); ++i)
		groups[i].shrinkToFit();
	vertices.shrink_to_fit();
	vertNormals.shrink_to_fit();
}

ostream &operator<<(ostream &out, const Mesh &mesh) {
	unsigned int triangleCount = 0;
	for(unsigned int i=0; i<mesh.groups.size(); ++i)
		triangleCount += mesh.groups[i].triangleCount();
	return out << "verts: " << mesh.vertices.size() << ", tris: " << triangleCount << ", groups: " << mesh.groups.size();
}


///////////////////
// TriangleGroup //
///////////////////

bool TriangleGroup::intersects(const Ray3 &ray, const Mesh &parent) const {
	return false;
}

double TriangleGroup::intersection(const Ray3 &ray, const Mesh &parent) const {
	return 1;
}

Collision TriangleGroup::collision(const Ray3 &ray, const Mesh &parent) const {
	Collision col;
	
	// iterate through the triangles
	unsigned short end = surfNormals.size();
	for(unsigned short i=0; i<end; ++i) {
		
		// skip back-facing triangles
		if (surfNormals[i].dot(ray.vector) >= 0)
			continue;
		
		// get base vertex and two edges from it
		unsigned short vertInd = i*3;
		Vec3 vertex1 = parent.vertices[indices[vertInd]];
		Vec3 edge1 = parent.vertices[indices[vertInd+1]] -vertex1;
		Vec3 edge2 = parent.vertices[indices[vertInd+2]] -vertex1;
		
		// calculate first intermediate value
		Vec3 h = ray.vector.cross(edge2);
		double a = edge1.dot(h);
		if (a > -0.0001 && a < 0.0001)
			continue;
		
		// calculate the "x" location of the collision on the triangle
		Vec3 diff = ray.position -vertex1;
		double planeX = diff.dot(h) /a;
		if (planeX < 0 || planeX > 1)
			continue;
		
		// calculate the "y" location of the collision on the triangle
		Vec3 q = diff.cross(edge1);
		double planeY = ray.vector.dot(q) /a;
		if (planeY < 0 || planeX+planeY > 1)
			continue;
		
		// calculate the distance to the collision
		double distance = edge2.dot(q) /a;
		
		// set new clostest collision parameters
		if (distance < col.distance && distance >= 0) {
			col.distance = distance;
			col.material = materials[i];
			
			// cache vertex normals
			const Vec3 &norm1 = parent.vertNormals[indices[vertInd]];
			const Vec3 &norm2 = parent.vertNormals[indices[vertInd+1]];
			const Vec3 &norm3 = parent.vertNormals[indices[vertInd+2]];
			
			// if we don't have vertex normals,  just use surface normal.  Otherwise, interpolate vertex normals
			if (parent.vertNormals.size() != parent.vertices.size() ||
					norm1.dot(norm2) < 0.1 || norm1.dot(norm3) < 0.1 || norm2.dot(norm3) < 0.1) {
				col.normal = surfNormals[i];
			} else {
				col.normal = norm1 *(1 -planeY -planeX);
				col.normal += norm2 *(planeX);
				col.normal += norm3 *(planeY);
			}
		}
	}
	col.position = ray.position +ray.vector *col.distance;
	col.normal.normalize();
	
	return col;
}

void TriangleGroup::addTriangle(unsigned short a, unsigned short b, unsigned short c, unsigned short material, const Mesh &parent) {
	indices.push_back(a);
	indices.push_back(b);
	indices.push_back(c);
	materials.push_back(material);
	
	// calculate surface normal
	surfNormals.push_back(((parent.vertices[b] -parent.vertices[a]).cross(parent.vertices[c] -parent.vertices[b])).normal());
}

unsigned int TriangleGroup::triangleCount() const {
	return indices.size() /3;
}

void TriangleGroup::shrinkToFit() {
	indices.shrink_to_fit();
	surfNormals.shrink_to_fit();
	materials.shrink_to_fit();
}
