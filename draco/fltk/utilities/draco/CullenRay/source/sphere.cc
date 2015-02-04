
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "sphere.h"

#include <cmath>
#include <cfloat>

using namespace std;


Sphere::Sphere(const Vec3 &position, double radius, unsigned short matIndex): position(position), radius(radius), material(matIndex) {}
Sphere::Sphere(const Sphere &source): position(source.position), radius(source.radius), material(source.material) {}

bool Sphere::intersects(const Ray3 &ray) const {
	Vec3 diff = position -ray.position;
	double v = diff.dot(ray.vector);
	return radius *radius -diff.lengthSquared() +v *v >= 0;
}

double Sphere::intersection(const Ray3 &ray) const {
	Vec3 diff = position -ray.position;
	double v = diff.dot(ray.vector);
	double dSqr = radius *radius -(diff.lengthSquared() -v *v);
	if (dSqr < 0) return DBL_MAX;
	return v -sqrt(dSqr);
}

Collision Sphere::collision(const Ray3 &ray) const {
	Collision col;
	Vec3 diff = position -ray.position;
	double v = diff.dot(ray.vector);
	double dSqr = radius *radius -(diff.lengthSquared() -v *v);
	if (dSqr < 0) return col;
	col.distance = v -sqrt(dSqr);
	col.material = material;
	col.position = ray.position +ray.vector *col.distance;
	col.normal = (col.position -position) /radius;
	col.shape = this;
	return col;
}

ostream &operator<<(ostream &out, const Sphere &sphere) {
	return out << "pos: " << sphere.position << ", rad: " << sphere.radius;
}

istream &operator>>(istream &in, Sphere &sphere) {
	in >> sphere.position;
	in >> sphere.radius;
	return in;
}