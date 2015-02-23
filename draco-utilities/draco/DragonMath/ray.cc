
#include "ray.h"

Ray3::Ray3(const Vector3<double> &position, const Vector3<double> &direction): position(position), direction(direction) {}
Ray3::Ray3(const Ray3 &source): position(source.position), direction(source.direction) {}

