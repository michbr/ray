#ifndef GL_CAMERA_OBJ_H
#define GL_CAMERA_OBJ_H

#include "DragonMath/dragonmath.h"


class Camera {
public:
	// members
	//std::string name;
	Vector3<double> position, direction, up;

	Camera(const Vector3<double> pos, const Vector3<double> dir, const Vector3<double> up);
	/*	float start_x, float start_y, float start_z,
		float vrp_x = 0, float vrp_y = 0, float vrp_z = 1,
		float upx = 0, float upy = 1, float upz = 0
	);*/

	//Camera(std::string, Vector3<double> start_pos, Vector3<double> vp_normal, Vector3<double> focal_point, double focal_length);

	//void setPerspective(float fovy, float aspect_ratio, float near_plane, float far_plane);

	//void LookAt(Vector3<double> target);
	//void Look(Vector3<float> look);
	//void rotate(float angle, int axis, Vector3<float> look);
	//std::string getName() const;
	//Vector3<double> getFocalPoint() const;
	//Vector3<double> getHorizontalAxis() const;
	//Vector3<double> getVerticalAxis() const;
	friend std::ostream &operator<<(std::ostream &os, const Camera &a) {
		//TODO fix this!!!
		os << a.position << "-" << a.direction << "-" << a.up;
		return os;
	}
};

#endif
