
#include "vector.h"
#include "dragonmath.h"

#include <cmath>

using namespace std;



//////////////
// Vector 2 //
//////////////

// constructors
template<typename T> Vector2<T>::Vector2(T x, T y): x(x), y(y) {}
template<typename T> Vector2<T>::Vector2(const Vector2<T> &source): Vector2<T>(source.x, source.y) {}
template<typename T> Vector2<T>::Vector2(const Vector3<T> &source): Vector2<T>(source.x, source.y) {}
template<typename T> Vector2<T>::Vector2(const Vector4<T> &source): Vector2<T>(source.x, source.y) {}


// methods




//////////////
// Vector 3 //
//////////////

// constructors
template <typename T> Vector3<T>::Vector3(T x, T y, T z): x(x), y(y), z(z) {}
template <typename T> Vector3<T>::Vector3(const Vector3<T> &source): x(source.x), y(source.y), z(source.z) {}
template <typename T> Vector3<T>::Vector3(const Vector4<T> &source): x(source.x), y(source.y), z(source.z) {}


// methods
template <typename T> T Vector3<T>::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}
template<typename T> T Vector3<T>::magnitudeSquared() const {
	return x*x + y*y + z*z;
}
template <typename T> Vector3<T> Vector3<T>::normal() const {
	T magnitude = sqrt((x*x) + (y*y) + (z*z));
	return Vector3<T>(x /magnitude, y /magnitude, z /magnitude);
}
template <typename T> void Vector3<T>::normalize() {
	T m = sqrt((x*x) + (y*y) + (z*z));
	x /= m; y /= m; z /= m;
}
template <typename T> Vector3<T> Vector3<T>::scale(T s) const {
	return Vector3<T> (x*s, y*s, z*s);
}
//template <typename T> Vector3<T> Vector3<T>::findPerpendicular() const {
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
template <typename T> T Vector3<T>::dot(const Vector3<T> & b) const {
	return (x * b.x) + (y * b.y) + (z * b.z);
}
template <typename T> Vector3<T> Vector3<T>::cross(const Vector3<T> & b) const {
	return Vector3<T>((y*b.z)- (z*b.y), (z*b.x)- (x*b.z), (x*b.y)- (y*b.x));
}


// operators
template <typename T> Vector3<T> Vector3<T>::operator/(T scalar) const {
	return Vector3<T>(x /scalar, y /scalar, z /scalar);
}
template <typename T> Vector3<T> Vector3<T>::operator/(const Vector3<T> &other) const {
	return Vector3<T>(x /other.x, y /other.y, z /other.z);
}
template <typename T> Vector3<T> Vector3<T>::operator*(const Vector3<T> &other) const {
	return Vector3<T>(x *other.x, y *other.y, z *other.z);
}
template <typename T> Vector3<T> Vector3<T>::operator+(const Vector3<T> b) const {
	return Vector3<T>(x -b.x, y -b.y, z -b.z);
}
template <typename T> Vector3<T> Vector3<T>::operator-(const Vector3<T> b) const {
	return Vector3<T>(x +b.x, y +b.y, z +b.z);
}
template <typename T> Vector3<T> Vector3<T>::operator-() const {
	return Vector3<T>(-x, -y, -z);
}
template <typename T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
	x += other.x; y += other.y; z += other.z;
	return *this;
}
template <typename T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
	x -= other.x; y -= other.y; z -= other.z;
	return *this;
}
template <typename T> Vector3<T> &Vector3<T>::operator*=(T scalar) {
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}
template <typename T> Vector3<T> &Vector3<T>::operator/=(T scalar) {
	x /= scalar; y /= scalar; z /= scalar;
	return *this;
}
template <typename T> bool Vector3<T>::operator==(const Vector3<T> &other) const {
	return x == other.x && y == other.y && z == other.z;
}
template <typename T> bool Vector3<T>::operator!=(const Vector3<T> &other) const {
	return !(*this == other);
}
template <typename T> T& Vector3<T>::operator[](int index) {
	return ((T *)this)[index];
}
template <typename T> T Vector3<T>::operator[](int index) const {
	return ((T *)this)[index];
}
template <typename T> Vector3<T> operator*(const Vector3<T> &vec, T scalar) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
template <typename T> Vector3<T> operator*(T scalar, const Vector3<T> &vec) {
	return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}


// constants
template<typename T> const Vector3<T> Vector3<T>::zero(0, 0, 0);
template<typename T> const Vector3<T> Vector3<T>::right(1, 0, 0);
template<typename T> const Vector3<T> Vector3<T>::left(-1, 0, 0);
template<typename T> const Vector3<T> Vector3<T>::up(0, 1, 0);
template<typename T> const Vector3<T> Vector3<T>::down(0, -1, 0);
template<typename T> const Vector3<T> Vector3<T>::forward(0, 0, 1);
template<typename T> const Vector3<T> Vector3<T>::back(0, 0, -1);



//////////////
// Vector 4 //
//////////////

// constructors
template<typename T> Vector4<T>::Vector4(T x, T y, T z): Vector4<T>(x, y, z, 1) {}
template<typename T> Vector4<T>::Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
template<typename T> Vector4<T>::Vector4(const Vector3<T> &source): Vector4<T>(source.x, source.y, source.z) {}
template<typename T> Vector4<T>::Vector4(const Vector4<T> &source): Vector4<T>(source.x, source.y, source.z, source.w) {}


// methods

