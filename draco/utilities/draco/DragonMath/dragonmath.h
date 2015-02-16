#ifndef GL_DRAGON_MATH_OBJ_H
#define GL_DRAGON_MATH_OBJ_H

#include "matrix.h"
#include "ray.h"
#include "vector.h"

#include <GL/gl.h>

template class Matrix<GLfloat>;
template class Matrix<GLdouble>;
template class Vector3<GLfloat>;
template class Vector3<GLdouble>;
template class Vector3<int>;

#endif
