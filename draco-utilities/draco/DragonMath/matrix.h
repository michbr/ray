#ifndef DRACO_MATRIX_OBJ_H
#define DRACO_MATRIX_OBJ_H

#include "EXPORT.h"

#include <iostream>

template<class T>
class Matrix {
private:
	T *m;
	int h;
	int w;

public:
	DRACO_DRAGON_MATH_API Matrix(int x, int y);

	DRACO_DRAGON_MATH_API const T *toArray();

	DRACO_DRAGON_MATH_API T &operator()(int x, int y);

	friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &a) {
		for (int i = 0; i < a.h * a.w; i++) {
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
