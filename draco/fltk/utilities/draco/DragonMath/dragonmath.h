#ifndef GL_DRAGON_MATH_OBJ_H
#define GL_DRAGON_MATH_OBJ_H

#include <iostream>

template <class T>
class Vector3 {
	private:
		T v[3];
	public:	
		//Vector3();
		Vector3(T x, T y, T z);
		Vector3 cross(Vector3 b);
	//	void normalize();
		T magnitude();

		//const T& operator[](int index);

		Vector3 normalize() const;
		Vector3 cross(const Vector3 & b) const;
		Vector3 scale (double) const;

		//static void equal(const Vector3 & a, const Vector3 & b);
		Vector3 findPerpendicular() const;

		T dot(const Vector3 & b) const;
		
		Vector3 operator-(const Vector3) const;
		Vector3 operator+(const Vector3) const;
		T& operator[](int index);
		T operator[](int index) const;

		friend std::ostream & operator<<(std::ostream& os, const Vector3<T> & a) {
			os << "(" << a.v[0] << ", " << a.v[1] << ", " << a.v[2] << ")";
			return os;
		}		
};

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
