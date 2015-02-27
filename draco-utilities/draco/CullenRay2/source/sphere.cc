
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../sphere.h"

#include <cmath>
#include <cfloat>

using namespace std;


Sphere::Sphere(const Vector3<double> &position, double radius, unsigned short matIndex): position(position), radius(radius), material(matIndex) {}
Sphere::Sphere(const Sphere &source): position(source.position), radius(source.radius), material(source.material) {}

bool Sphere::intersects(const Ray3<double> &ray) const {
	Vector3<double> diff = position -ray.position;
	double v = diff.dot(ray.direction);
	return radius *radius -diff.magnitudeSquared() +v *v >= 0;
}

double Sphere::intersection(const Ray3<double> &ray) const {
	Vector3<double> diff = position -ray.position;
	double v = diff.dot(ray.direction);
	double dSqr = radius *radius -(diff.magnitudeSquared() -v *v);
	if (dSqr < 0) return DBL_MAX;
	return v -sqrt(dSqr);
}

Collision Sphere::collision(const Ray3<double> &ray) const {
	Collision col;
	Vector3<double> diff = position -ray.position;
	double v = diff.dot(ray.direction);
	double dSqr = radius *radius -(diff.magnitudeSquared() -v *v);
	if (dSqr < 0) return col;
	col.distance = v -sqrt(dSqr);
	col.material = material;
	col.position = ray.position +ray.direction *col.distance;
	col.normal = (col.position -position) /radius;
	col.shape = this;
	return col;
}

ostream &operator<<(ostream &out, const Sphere &sphere) {
	return out << "pos: " << sphere.position << ", rad: " << sphere.radius;
}

/*istream &operator>>(istream &in, Sphere &sphere) {
	in >> sphere.position;
	in >> sphere.radius;
	return in;
}*/
