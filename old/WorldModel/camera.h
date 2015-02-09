#ifndef GL_CAMERA_OBJ_H
#define GL_CAMERA_OBJ_H

#include "dragonmath.h"

class Camera {
    private:
	   std::string name;

	   Vector3<double> pos;
	   Vector3<float> look;
	   Vector3<double> up;
	  
	   Vector3<double> fp;
	   Vector3<double> vpn;
	   double focalLength; 
    public:
	Camera(
		float start_x, float start_y, float start_z,
		float vrp_x = 0, float vrp_y = 0, float vrp_z = 1,
		float upx = 0, float upy = 1, float upz = 0
	);
	Camera(std::string, Vector3<double> start_pos, Vector3<double> vp_normal, Vector3<double> focal_point, double focal_length);
	void setPerspective(float fovy, float aspect_ratio, float near_plane, float far_plane);
	void LookAt(float vrp_x, float vrp_y, float vrp_z);
	void Look();
	void rotate(float angle, int axis);
	void drawQuad();
	void drawCube();

	std::string getName();
	
	const Vector3<double> & getPos();
	const Vector3<double> & getFocalPoint();
	Vector3<double> getHorizontalAxis();
	Vector3<double> getVerticalAxis();

	friend std::ostream & operator<<(std::ostream& os, const Camera & a) {
		os << a.pos << "-" << a.look << "-" << a.up;
		return os;
	}
};

#endif
