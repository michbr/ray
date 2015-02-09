
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_SHAPE_H
#define RAY_SHAPE_H

#include "math.h"
#include "material.h"

#include <iostream>

class Shape;

class Collision {
	public:
		Vec3 normal;
		Vec4 position;
		double distance;
		unsigned short material;
		const Shape *shape;
		
		Collision();
		Collision(const Collision &source);
};


class Shape {
	public:
		
		// must be normalized ray
		virtual bool intersects(const Ray3 &ray) const = 0;
		virtual double intersection(const Ray3 &ray) const = 0;
		virtual Collision collision(const Ray3 &ray) const = 0;
};

#endif // RAY_SHAPE_H
