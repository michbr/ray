#include "dragonmath.h"
#include <GL/gl.h>
#include <cmath>

using namespace std;

template <class T> Vector3<T>::Vector3(T x, T y, T z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

template <class T> T Vector3<T>::magnitude() {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

/*template <class T> void Vector3<T>::normalize() {
	T mag = magnitude();
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}*/

template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> b) {
	T x = v[1]*b.v[2] - v[2]*b.v[1];
	T y = v[2]*b.v[0] - v[0]*b.v[2];
	T z = v[0]*b.v[1] - v[1]*b.v[0];
	return Vector3<T>(x, y, z);
}

template <class T> Vector3<T> Vector3<T>::operator-(const Vector3<T> b) const {
	T x = v[0] - b.v[0];
	T y = v[1] - b.v[1];
	T z = v[2] - b.v[2];
	
	return Vector3<T>(x, y, z);
}

template <class T> Vector3<T> Vector3<T>::operator+(const Vector3<T> b) const {
	T x = v[0] + b.v[0];
	T y = v[1] + b.v[1];
	T z = v[2] + b.v[2];
	
	return Vector3<T>(x, y, z);
}

template <class T> T& Vector3<T>::operator[](int index) {
	return v[index];
}

template <class T> T Vector3<T>::operator[](int index) const {
	return v[index];
}

template <class T> Vector3<T> Vector3<T>::normalize() const {
    double magnitude = sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]));
    Vector3<T> normal = Vector3<T>(
							(v[0]/magnitude),
							(v[1]/magnitude),
							(v[2]/magnitude));
	return normal;
}

template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> & b) const {
	Vector3<T> result = Vector3<T>(
							(v[1]*b[2])- (v[2]*b[1]),
							(v[2]*b[0])- (v[0]*b[2]),
							(v[0]*b[1])- (v[1]*b[0]));
	return result;
}

template <class T> Vector3<T> Vector3<T>::scale (double x) const {
	Vector3<T> result = Vector3<T> ((v[0]*x), (v[1]*x), (v[2]*x));
	return result;
}

template <class T> Vector3<T> Vector3<T>::findPerpendicular() const {
        int index = 0;
        Vector3<T> axis = Vector3<T>(v[0], v[1], v[2]);
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
	return (v[0] * b[0]) + (v[1] * b[1]) + (v[2] * b[2]);
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
