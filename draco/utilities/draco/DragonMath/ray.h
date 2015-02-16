#ifndef RAY_OBJECT_H
#define RAY_OBJECT_H

#include "vector.h"

/***********
Proposed changes:
	-position and vector become private

***********/

class Ray3 {
	private:
                Vector3<double> position, vector;
        public:


                Ray3();
                Ray3(const Vector3<double> &position, const Vector3<double> &vector);
                Ray3(const Ray3 &source);
		const Vector3<double> & getPosition() const;
		const Vector3<double> & getDirection() const;
};

#endif
