#ifndef RAY_OBJECT_H
#define RAY_OBJECT_H

#include "vector.h"
#include "EXPORT.h"

/***********
Proposed changes:
-position and vector become private

***********/

template<class T>
class Ray3 {
public:
	Vector3<T> position, direction;

	DRACO_DRAGON_MATH_API Ray3(const Vector3<T> &position, const Vector3<T> &direction);
	DRACO_DRAGON_MATH_API Ray3(const Ray3<T> &source);
};

#endif
