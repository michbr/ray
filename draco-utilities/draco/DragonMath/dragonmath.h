#ifndef GL_DRAGON_MATH_OBJ_H
#define GL_DRAGON_MATH_OBJ_H

#include "EXPORT.h"

#include "matrix.h"
#include "quaternion.h"
#include "ray.h"
#include "vector.h"

template class Matrix<double>;
template class Matrix<float>;

template class Ray3<double>;
template class Ray3<float>;
template class Ray3<long>;
template class Ray3<int>;
template class Ray3<short>;

template class Vector2<double>;
template class Vector2<float>;
template class Vector2<long>;
template class Vector2<int>;
template class Vector2<short>;
template class Vector2<unsigned char>;
template class Vector3<double>;
template class Vector3<float>;
template class Vector3<long>;
template class Vector3<int>;
template class Vector3<short>;
template class Vector3<unsigned char>;
template class Vector4<double>;
template class Vector4<float>;
template class Vector4<long>;
template class Vector4<int>;
template class Vector4<short>;
template class Vector4<unsigned char>;


// function export
#ifdef DLL_EXPORT_DRACO_DRAGON_MATH

	// Vector 2
	template DRACO_DRAGON_MATH_API Vector2<double> operator*<double>(const Vector2<double> &, double);
	template DRACO_DRAGON_MATH_API Vector2<double> operator*<double>(double, const Vector2<double> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<double>(std::ostream &out, const Vector2<double> &vec);
	template DRACO_DRAGON_MATH_API Vector2<float> operator*<float>(const Vector2<float> &, float);
	template DRACO_DRAGON_MATH_API Vector2<float> operator*<float>(float, const Vector2<float> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<float>(std::ostream &out, const Vector2<float> &vec);
	template DRACO_DRAGON_MATH_API Vector2<long> operator*<long>(const Vector2<long> &, long);
	template DRACO_DRAGON_MATH_API Vector2<long> operator*<long>(long, const Vector2<long> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<long>(std::ostream &out, const Vector2<long> &vec);
	template DRACO_DRAGON_MATH_API Vector2<int> operator*<int>(const Vector2<int> &, int);
	template DRACO_DRAGON_MATH_API Vector2<int> operator*<int>(int, const Vector2<int> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<int>(std::ostream &out, const Vector2<int> &vec);
	template DRACO_DRAGON_MATH_API Vector2<short> operator*<short>(const Vector2<short> &, short);
	template DRACO_DRAGON_MATH_API Vector2<short> operator*<short>(short, const Vector2<short> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<short>(std::ostream &out, const Vector2<short> &vec);
	template DRACO_DRAGON_MATH_API Vector2<unsigned char> operator*<unsigned char>(const Vector2<unsigned char> &, unsigned char);
	template DRACO_DRAGON_MATH_API Vector2<unsigned char> operator*<unsigned char>(unsigned char, const Vector2<unsigned char> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<unsigned char>(std::ostream &out, const Vector2<unsigned char> &vec);

	// Vector 3
	template DRACO_DRAGON_MATH_API Vector3<double> operator*<double>(const Vector3<double> &, double);
	template DRACO_DRAGON_MATH_API Vector3<double> operator*<double>(double, const Vector3<double> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<double>(std::ostream &out, const Vector3<double> &vec);
	template DRACO_DRAGON_MATH_API Vector3<float> operator*<float>(const Vector3<float> &, float);
	template DRACO_DRAGON_MATH_API Vector3<float> operator*<float>(float, const Vector3<float> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<float>(std::ostream &out, const Vector3<float> &vec);
	template DRACO_DRAGON_MATH_API Vector3<long> operator*<long>(const Vector3<long> &, long);
	template DRACO_DRAGON_MATH_API Vector3<long> operator*<long>(long, const Vector3<long> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<long>(std::ostream &out, const Vector3<long> &vec);
	template DRACO_DRAGON_MATH_API Vector3<int> operator*<int>(const Vector3<int> &, int);
	template DRACO_DRAGON_MATH_API Vector3<int> operator*<int>(int, const Vector3<int> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<int>(std::ostream &out, const Vector3<int> &vec);
	template DRACO_DRAGON_MATH_API Vector3<short> operator*<short>(const Vector3<short> &, short);
	template DRACO_DRAGON_MATH_API Vector3<short> operator*<short>(short, const Vector3<short> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<short>(std::ostream &out, const Vector3<short> &vec);
	template DRACO_DRAGON_MATH_API Vector3<unsigned char> operator*<unsigned char>(const Vector3<unsigned char> &, unsigned char);
	template DRACO_DRAGON_MATH_API Vector3<unsigned char> operator*<unsigned char>(unsigned char, const Vector3<unsigned char> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<unsigned char>(std::ostream &out, const Vector3<unsigned char> &vec);

	// Vector 4
	template DRACO_DRAGON_MATH_API Vector4<double> operator*<double>(const Vector4<double> &, double);
	template DRACO_DRAGON_MATH_API Vector4<double> operator*<double>(double, const Vector4<double> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<double>(std::ostream &out, const Vector4<double> &vec);
	template DRACO_DRAGON_MATH_API Vector4<float> operator*<float>(const Vector4<float> &, float);
	template DRACO_DRAGON_MATH_API Vector4<float> operator*<float>(float, const Vector4<float> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<float>(std::ostream &out, const Vector4<float> &vec);
	template DRACO_DRAGON_MATH_API Vector4<long> operator*<long>(const Vector4<long> &, long);
	template DRACO_DRAGON_MATH_API Vector4<long> operator*<long>(long, const Vector4<long> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<long>(std::ostream &out, const Vector4<long> &vec);
	template DRACO_DRAGON_MATH_API Vector4<int> operator*<int>(const Vector4<int> &, int);
	template DRACO_DRAGON_MATH_API Vector4<int> operator*<int>(int, const Vector4<int> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<int>(std::ostream &out, const Vector4<int> &vec);
	template DRACO_DRAGON_MATH_API Vector4<short> operator*<short>(const Vector4<short> &, short);
	template DRACO_DRAGON_MATH_API Vector4<short> operator*<short>(short, const Vector4<short> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<short>(std::ostream &out, const Vector4<short> &vec);
	template DRACO_DRAGON_MATH_API Vector4<unsigned char> operator*<unsigned char>(const Vector4<unsigned char> &, unsigned char);
	template DRACO_DRAGON_MATH_API Vector4<unsigned char> operator*<unsigned char>(unsigned char, const Vector4<unsigned char> &);
	template DRACO_DRAGON_MATH_API std::ostream &operator<<<unsigned char>(std::ostream &out, const Vector4<unsigned char> &vec);

#endif


#endif
