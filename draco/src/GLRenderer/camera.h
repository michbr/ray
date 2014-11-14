#ifndef GL_CAMERA_OBJ_H
#define GL_CAMERA_OBJ_H

#include "dragonmath.h"

template <class T> class Camera {
    private:
	   Vector3<T> pos;
	   Vector3<T> look;
	   Vector3<T> up;
	   
    public:
	Camera(
		T start_x, T start_y, T start_z,
		T vrp_x = 0, T vrp_y = 0, T vrp_z = 1,
		T upx = 0, T upy = 1, T upz = 0
	);
	void setPerspective(T fovy, T aspect_ratio, T near_plane, T far_plane);
	void LookAt(T vrp_x, T vrp_y, T vrp_z);
	void Look();
	void rotate(T angle, int axis);
	void drawQuad();
	void drawCube();
	friend std::ostream & operator<<(std::ostream& os, const Camera<T> & a) {
		os << a.pos << "-" << a.look << "-" << a.up;
		return os;
	}
};

#endif
