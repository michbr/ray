#ifndef GL_DRAGON_MATH_OBJ_H
#define GL_DRAGON_MATH_OBJ_H

#include "vector.h"

#include <iostream>


/*template <class T>
class Vector3 {
	private:
		T x;
		T y;
		T z;
	public:	
		//Vector3();
		Vector3(T x, T y, T z);
		Vector3 cross(Vector3 b);
	//	void normalize();
		T magnitude();

		//const T& operator[](int index);

		Vector3 normalize() const;
		Vector3 cross(const Vector3 & b) const;
		Vector3 scale (T scalar) const;

		//static void equal(const Vector3 & a, const Vector3 & b);
		Vector3 findPerpendicular() const;

		T dot(const Vector3 & b) const;
		
		Vector3 operator-(const Vector3) const;
		Vector3 operator+(const Vector3) const;
		T& operator[](int index);
		T operator[](int index) const;

		friend std::ostream & operator<<(std::ostream& os, const Vector3<T> & a) {
			os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
			return os;
		}		
};*/

/*template <class T>
class Vector4 {
	public:
		
		// constants
		static const Vector4<T> zeroAbsolute;
		static const Vector4<T> zero;
		static const Vector4<T> one;
		static const Vector4<T> right;
		static const Vector4<T> up;
		static const Vector4<T> forward;
		
		// members
		T x, y, z, w;
		
		// constructors
		Vector4();
		Vector4(T x, T y, T z);
		Vector4(T x, T y, T z, T w);
		Vector4(const Vector3<T> &source);
		Vector4(const Vector4 &source);
		
		// methods
		T& operator[](int index);
		T operator[](int index) const;
		T length() const;
		T lengthSquared() const;
		T distance(const Vector4 &other) const;
		T dot(const Vector4 &other) const;
		Vector4 normal() const;
		void normalize();
		Vector4 cross(const Vector4 &other) const;
		Vector4 operator/(T scalar) const;
		Vector4 operator/(const Vector4 &other) const;
		Vector4 operator*(const Vector4 &other) const;
		Vector4 operator+(const Vector4 &other) const;
		Vector4 operator-(const Vector4 &other) const;
		Vector4 operator-() const;
                Vector4 &operator+=(const Vector4 &other);
                Vector4 &operator-=(const Vector4 &other);
                Vector4 &operator*=(T scalar);
                Vector4 &operator/=(T scalar);
		bool operator==(const Vector4 &other) const;
		bool operator!=(const Vector4 &other) const;
};

template <class T>
Vector4<T> operator*(const Vector4<T> &vec, T scalar);
template <class T>
Vector4<T> operator*(T scalar, const Vector4<T> &vec);
template <class T>
std::ostream &operator<<(std::ostream &out, const Vector4<T> &vec);
template <class T>
std::istream &operator>>(std::istream &in, Vector4<T> &vec);*/


template <class T>
class Matrix {
	private:
		T * m;
		int h;
		int w;

	public:
		Matrix(int x, int y);
		const T * toArray();
		T& operator()(int x, int y);
		friend std::ostream & operator<<(std::ostream& os, const Matrix<T> & a) {
			for (int i = 0; i < a.h*a.w; i++) {
				//os << "[";
				//for (int j = 0; j < a.w; j++) {
					//if (j != 0) os << ", ";
					//os << i + j*a.h;
					os << a.m[i] << " ";
				//}
				//os << "]" << std::endl;
			}
			return os;
		}
};



#endif
