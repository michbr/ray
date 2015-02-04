
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_SPHERE_H
#define RAY_SPHERE_H

#include "math.h"
#include "shape.h"

#include <iostream>


class Sphere: public Shape {
	public:
		Vec3 position;
		double radius;
		unsigned short material;
		
		Sphere(const Vec3 &position, double radius, unsigned short materialIndex);
		Sphere(const Sphere &source);
		
		// must be normalized ray
		bool intersects(const Ray3 &ray) const;
		double intersection(const Ray3 &ray) const;
		Collision collision(const Ray3 &ray) const;
};

std::ostream &operator<<(std::ostream &out, const Sphere &sphere);
std::istream &operator>>(std::istream &in, Sphere &sphere);

#endif // RAY_SPHERE_H