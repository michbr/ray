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

template <class T> void Vector3<T>::normalize() {
	T mag = magnitude();
	v[0] = v[0]/mag;
	v[1] = v[1]/mag;
	v[2] = v[2]/mag;
}

template <class T> Vector3<T> Vector3<T>::cross(Vector3<T> b) {
	T x = v[1]*b.v[2] - v[2]*b.v[1];
	T y = v[2]*b.v[0] - v[0]*b.v[2];
	T z = v[0]*b.v[1] - v[1]*b.v[0];
	return Vector3<T>(x, y, z);
}

template <class T> Vector3<T> Vector3<T>::operator-(Vector3<T> b) {
	T x = v[0] - b.v[0];
	T y = v[1] - b.v[1];
	T z = v[2] - b.v[2];
	
	return Vector3<T>(x, y, z);
}

template <class T> T& Vector3<T>::operator[](int index) {
	return v[index];
}

template <class T> void Vector3<T>::normalize(Vector3<T> & in, Vector3<T> & out) {
        double magnitude = sqrt((in[0]*in[0]) + (in[1]*in[1]) + (in[2]*in[2]));
        Vector3<T> * normal = new Vector3<T>();
        (*normal)[0] = (in[0]/magnitude);
        (*normal)[1] = (in[1]/magnitude);
        (*normal)[2] = (in[2]/magnitude);
	out = *normal;
}

template <class T> void Vector3<T>::cross(Vector3<T> & a, Vector3<T> & b, Vector3<T> & out) {
	Vector3<T> * result = new Vector3<T>();
        (*result)[0] = (a[1]*b[2])- (a[2]*b[1]) ;
        (*result)[1] = (a[2]*b[0])- (a[0]*b[2]) ;
        (*result)[2] = (a[0]*b[1])- (a[1]*b[0]) ;
	out = *result;
}

template <class T> void Vector3<T>::scale (Vector3<T> & a, double x, Vector3<T> & out) {
	Vector3<T> * result = new Vector3<T>();
	(*result)[0] = (a[0]*x);
	(*result)[1] = (a[1]*x);
	(*result)[2] = (a[2]*x);
	out = *result;
}

template <class T> void Vector3<T>::findPerpendicular(Vector3<T> & a, Vector3 & out) {
        int index = 0;
        Vector3<T> axis = Vector3<T>();
        axis[0] = a[0];
        axis[1] = a[1];
        axis[2] = a[2];
        double min = axis[0];

        for (int i = 1; i < 3; i++) {
                if (axis[i] < min) {
                        index = i;
                        min = axis[i];
                }
        }

        axis[index] = 1;
        Vector3<T>::normalize(axis, out);
}

template <class T> T Vector3<T>::dot(Vector3<T> & a, Vector3<T> & b) {
	return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

template <class T> T Vector3<T>::magnitude(Vector3<T> & a) {
	return sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
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
