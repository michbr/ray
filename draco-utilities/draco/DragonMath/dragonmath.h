#ifndef GL_DRAGON_MATH_OBJ_H
#define GL_DRAGON_MATH_OBJ_H

#include "EXPORT.h"

#include "matrix.h"
#include "ray.h"
#include "vector.h"

template class Matrix<double>;
template class Matrix<float>;
template class Vector3<double>;
template class Vector3<float>;
template class Vector3<long>;
template class Vector3<int>;
template class Vector3<short>;
template class Vector3<unsigned char>;

#ifdef DLL_EXPORT_DRACO_DRAGON_MATH

template DRACO_DRAGON_MATH_API Vector3<double> operator*<double>(const Vector3<double> &, double);
template DRACO_DRAGON_MATH_API Vector3<double> operator*<double>(double, const Vector3<double> &);
template DRACO_DRAGON_MATH_API std::ostream &operator<<<double>(std::ostream &out, const Vector3<double> &vec);

#endif

#endif
