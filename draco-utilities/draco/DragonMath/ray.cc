
#include "ray.h"


template<class T> Ray3<T>::Ray3(const Vector3<T> &position, const Vector3<T> &direction): position(position), direction(direction) {}
template<class T> Ray3<T>::Ray3(const Ray3<T> &source): position(source.position), direction(source.direction) {}

