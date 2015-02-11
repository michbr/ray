#include "dragonmath.h"
#include <GL/gl.h>
#include <cmath>

using namespace std;

template <class T> Vector3<T>::Vector3(T xVal, T yVal, T zVal) {
	x = xVal;
	y = yVal;
	y = zVal;
}

template <class T> T Vector3<T>::magnitude() {
	return sqrt(x*x + y*y + z*z);
}

/*template <class T> void Vector3<T>::normalize() {
	T mag = magnitude();
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}*/

template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> b) {
	T i = y*b.z - z*b.y;
	T j = z*b.x - x*b.z;
	T k = x*b.y - y*b.x;
	return Vector3<T>(i, j, k);
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

template <class T> T& Vector3<T>::operator[](int index) {
	return ((T *)this)[index];
}

template <class T> T Vector3<T>::operator[](int index) const {
	return ((T *)this)[index];
}

template <class T> Vector3<T> Vector3<T>::normalize() const {
    double magnitude = sqrt((x*x) + (y*y) + (z*z));
    Vector3<T> normal = Vector3<T>(
							(x/magnitude),
							(x/magnitude),
							(x/magnitude));
	return normal;
}

template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> & b) const {
	Vector3<T> result = Vector3<T>(
							(y*b.z)- (z*b.y),
							(z*b.x)- (x*b.z),
							(x*b.y)- (y*b.x));
	return result;
}

template <class T> Vector3<T> Vector3<T>::scale (T s) const {
	Vector3<T> result = Vector3<T> ((x*s), (y*s), (z*s));
	return result;
}

template <class T> Vector3<T> Vector3<T>::findPerpendicular() const {
        int index = 0;
        Vector3<T> axis = Vector3<T>(x, y, z);
        double min = axis[0];

        for (int i = 1; i < 3; i++) {
                if (axis[i] < min) {
                        index = i;
                        min = axis[i];
                }
        }

        axis[index] = 1;
        return axis.normalize();
}

template <class T> T Vector3<T>::dot(const Vector3<T> & b) const {
	return (x * b.x) + (y * b.y) + (z * b.z);
}

//template <class T> std::ostream & operator<<(std::ostream& os, const Vector3<T> a) {
//	os << "(" << a.v[0] << ", " << a.v[1] << ", " << v[2] << ")" << endl;
//	return os;
//}

/*******************************************/
//										   *
// The Matrix data structure			   *
//										   *
/******************************************/


template <class T> Matrix<T>::Matrix(int x, int y) {
	m = new T[y*x];
	h = y;
	w = x;
}

template <class T> T& Matrix<T>::operator()(int x, int y) {
	return m[w*x + y];
}

template <class T> const T* Matrix<T>::toArray() {
	return m;
}

template class Matrix<GLfloat>;
template class Matrix<GLdouble>;
template class Vector3<GLfloat>;
template class Vector3<GLdouble>;
template class Vector3<int>;
