
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_CAMERA_H
#define RAY_CAMERA_H

#include "dragonmath.h"
#include <iostream>


class Camera {
	public:
		std::string name;			// the name of the camera
		Vector3<double> position, normal, up;	// the PRP, VPN, and up vector of the camera.  Essentially the transform
		double near, far;			// the distances for the near and far clipping planes
		
		// constructs the camera with given parameters
		Camera(const std::string &name, const Vector3<double> &position, const Vector3<double> &normal, const Vector3<double> &up, double near, double far);
};

// outputs the camera's state or data
std::ostream &operator<<(std::ostream &out, const Camera &cam);

#endif // RAY_CAMERA_H
