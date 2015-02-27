
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_SHAPE_H
#define RAY_SHAPE_H

#include "dragonmath.h"
#include "material.h"

#include <iostream>

class Shape;

class Collision {
	public:
		Vector3<double> normal;
		Vector4<double> position;
		double distance;
		unsigned short material;
		const Shape *shape;
		
		Collision();
		Collision(const Collision &source);
};


class Shape {
	public:
		
		// must be normalized ray
		virtual bool intersects(const Ray3<double> &ray) const = 0;
		virtual double intersection(const Ray3<double> &ray) const = 0;
		virtual Collision collision(const Ray3<double> &ray) const = 0;
};

#endif // RAY_SHAPE_H
