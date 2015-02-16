#include "dragonmath.h"

Ray3::Ray3(): position(Vector3<double>()), vector(Vector3<double>()) {}
Ray3::Ray3(const Vector3<double> &position, const Vector3<double> &vector): position(position), vector(vector) {}
Ray3::Ray3(const Ray3 &source): position(source.position), vector(source.vector) {}

