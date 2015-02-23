#include "dragonmath.h"

#include <GL/gl.h>
#include <cmath>

using namespace std;

template <class T> Vector3<T>::Vector3(T xVal, T yVal, T zVal) {
	x = xVal;
	y = yVal;
	z = zVal;
}

template <class T> Vector3<T>::Vector3(const Vector3<T> &source): Vector3<T>(source.x, source.y, source.z) {}
template <class T> Vector3<T>::Vector3(const Vector4<T> &source): Vector3<T>(source.x, source.y, source.z) {}

template <class T> T Vector3<T>::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

/*template <class T> void Vector3<T>::normalize() {
	T mag = magnitude();
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}*/

template <class T> Vector3<T> Vector3<T>::operator/(T scalar) const {
	return Vector3<T>(x /scalar, y /scalar, z /scalar);
}
template <class T> Vector3<T> Vector3<T>::operator/(const Vector3<T> &other) const {
	return Vector3<T>(x /other.x, y /other.y, z /other.z);
}
template <class T> Vector3<T> Vector3<T>::operator*(const Vector3<T> &other) const {
	return Vector3<T>(x *other.x, y *other.y, z *other.z);
}

template <class T> Vector3<T> Vector3<T>::operator-(const Vector3<T> b) const {
	T i = x - b.x;
	T j = y - b.y;
	T k = z - b.z;

	return Vector3<T>(i, j, k);
}

template <class T> Vector3<T> Vector3<T>::operator+(const Vector3<T> b) const {
	T i = x + b.x;
	T j = y + b.y;
	T k = z + b.z;

	return Vector3<T>(i, j, k);
}

template <class T> Vector3<T> Vector3<T>::operator-() const {
	return Vector3<T>(-x, -y, -z);
}
template <class T> bool Vector3<T>::operator==(const Vector3<T> &other) const {
	return x == other.x && y == other.y && z == other.z;
}
template <class T> bool Vector3<T>::operator!=(const Vector3<T> &other) const {
	return !(*this == other);
}
template <class T> Vector3<T> operator*(const Vector3<T> &vec, T scalar) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
template <class T> Vector3<T> operator*(T scalar, const Vector3<T> &vec) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
template <class T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
	x += other.x; y += other.y; z += other.z;
	return *this;
}
template <class T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
	x -= other.x; y -= other.y; z -= other.z;
	return *this;
}
template <class T> Vector3<T> &Vector3<T>::operator*=(T scalar) {
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}
template <class T> Vector3<T> &Vector3<T>::operator/=(T scalar) {
	x /= scalar; y /= scalar; z /= scalar;
	return *this;
}

template <class T> T& Vector3<T>::operator[](int index) {
	return ((T *)this)[index];
}

template <class T> T Vector3<T>::operator[](int index) const {
	return ((T *)this)[index];
}

template <class T> Vector3<T> Vector3<T>::normal() const {
	T magnitude = sqrt((x*x) + (y*y) + (z*z));
	Vector3<T> normal = Vector3<T>((x/magnitude),
				   (y/magnitude),
				   (z/magnitude));
	return normal;
}

template <class T> void Vector3<T>::normalize() {
	T magnitude = sqrt((x*x) + (y*y) + (z*z));
	x = (x/magnitude);
	y = (y/magnitude);
	z = (z/magnitude);
}

template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> & b) const {
	return Vector3<T>((y*b.z)- (z*b.y), (z*b.x)- (x*b.z), (x*b.y)- (y*b.x));
}

template <class T> Vector3<T> Vector3<T>::scale (T s) const {
	Vector3<T> result = Vector3<T> ((x*s), (y*s), (z*s));
	return result;
}

//template <class T> Vector3<T> Vector3<T>::findPerpendicular() const {
//	int index = 0;
//	Vector3<T> axis = Vector3<T>(x, y, z);
//	T min = axis[0];
//
//	for (int i = 1; i < 3; i++) {
//		if (axis[i] < min) {
//			index = i;
//			min = axis[i];
//		}
//	}
//
//	axis[index] = 1;
//	axis.normalize();
//	return axis;
//}

template <class T> T Vector3<T>::dot(const Vector3<T> & b) const {
	return (x * b.x) + (y * b.y) + (z * b.z);
}

