#ifndef RAY_OBJECT_H
#define RAY_OBJECT_H

#include "vector.h"
#include "dragonMath.h"

/***********
Proposed changes:
-position and vector become private

***********/

class Ray3 {
public:
	Vector3<double> position, direction;

	Ray3(const Vector3<double> &position, const Vector3<double> &direction);
	Ray3(const Ray3 &source);
	const Vector3<double> &getPosition() const;
	const Vector3<double> &getDirection() const;
};

#endif
