#include "dragonmath.h"
#include "../CullenRay/math.h"

#include <cmath>

using namespace std;



//////////////
// Vector 2 //
//////////////

// constructors
Vec2::Vec2(): Vec2(0, 0) {}
Vec2::Vec2(T x, T y): x(x), y(y) {}
Vec2::Vec2(const Vec2 &source): Vec2(source.x, source.y) {}
Vec2::Vec2(const Vec3 &source): Vec2(source.x, source.y) {}
Vec2::Vec2(const Vec4 &source): Vec2(source.x, source.y) {}


// methods




//////////////
// Vector 3 //
//////////////

// constructors
template <class T> Vector3<T>::Vector3(T x, T y, T z): x(x), y(y), z(z) {}
template <class T> Vector3<T>::Vector3(const Vector3<T> &source): x(source.x), y(source.y), z(source.z) {}
template <class T> Vector3<T>::Vector3(const Vector4<T> &source): x(source.x), y(source.y), z(source.z) {}
template <class T> Vector3<T>::Vector3(const Vector3<T> &source): x(source.x), y(source.y), z(source.z) {}
template <class T> Vector3<T>::Vector3(const Vector4<T> &source): x(source.x), y(source.y), z(source.z) {}


// methods
template <class T> T Vector3<T>::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}
template<class T> T Vector3<T>::magnitudeSquared() const {
	return x*x + y*y + z*z;
}
template <class T> Vector3<T> Vector3<T>::normal() const {
	T magnitude = sqrt((x*x) + (y*y) + (z*z));
	return Vector3<T>(x /magnitude, y /magnitude, z /magnitude);
}
template <class T> void Vector3<T>::normalize() {
	T m = sqrt((x*x) + (y*y) + (z*z));
	x /= m; y /= m; z /= m;
}
template <class T> Vector3<T> Vector3<T>::scale(T s) const {
	return Vector3<T> (x*s, y*s, z*s);
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
template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> & b) const {
	return Vector3<T>((y*b.z)- (z*b.y), (z*b.x)- (x*b.z), (x*b.y)- (y*b.x));
}


// operators
template <class T> Vector3<T> Vector3<T>::operator/(T scalar) const {
	return Vector3<T>(x /scalar, y /scalar, z /scalar);
}
template <class T> Vector3<T> Vector3<T>::operator/(const Vector3<T> &other) const {
	return Vector3<T>(x /other.x, y /other.y, z /other.z);
}
template <class T> Vector3<T> Vector3<T>::operator*(const Vector3<T> &other) const {
	return Vector3<T>(x *other.x, y *other.y, z *other.z);
}
template <class T> Vector3<T> Vector3<T>::operator+(const Vector3<T> b) const {
	return Vector3<T>(x -b.x, y -b.y, z -b.z);
}
template <class T> Vector3<T> Vector3<T>::operator-(const Vector3<T> b) const {
	return Vector3<T>(x +b.x, y +b.y, z +b.z);
}
template <class T> Vector3<T> Vector3<T>::operator-() const {
	return Vector3<T>(-x, -y, -z);
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
template <class T> bool Vector3<T>::operator==(const Vector3<T> &other) const {
	return x == other.x && y == other.y && z == other.z;
}
template <class T> bool Vector3<T>::operator!=(const Vector3<T> &other) const {
	return !(*this == other);
}
template <class T> T& Vector3<T>::operator[](int index) {
	return ((T *)this)[index];
}
template <class T> T Vector3<T>::operator[](int index) const {
	return ((T *)this)[index];
}
template <class T> Vector3<T> operator*(const Vector3<T> &vec, T scalar) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
template <class T> Vector3<T> operator*(T scalar, const Vector3<T> &vec) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}


// constants
const Vec3 Vec3::zero(0, 0, 0);
const Vec3 Vec3::right(1, 0, 0);
const Vec3 Vec3::left(-1, 0, 0);
const Vec3 Vec3::up(0, 1, 0);
const Vec3 Vec3::down(0, -1, 0);
const Vec3 Vec3::forward(0, 0, 1);
const Vec3 Vec3::back(0, 0, -1);



//////////////
// Vector 4 //
//////////////

// constructors
Vec4::Vec4(): Vec4(0, 0, 0) {}
Vec4::Vec4(double x, double y, double z): Vec4(x, y, z, 1) {}
Vec4::Vec4(double x, double y, double z, double w): x(x), y(y), z(z), w(w) {}
Vec4::Vec4(const Vec3 &source): Vec4(source.x, source.y, source.z) {}
Vec4::Vec4(const Vec4 &source): Vec4(source.x, source.y, source.z, source.w) {}

// methods
