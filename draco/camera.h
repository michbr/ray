#ifndef CAMERA_OBJECT_H
#define CAMERA_OBJECT_H

#include "wireframe.h"
#include "light.h"
#include "dragonmath.h"

#include <string>

class Camera {
	private:
		std::string name;

		double x,y,z;
		double focal_length;

		Vector3<double> * vpn;
		Vector3<double> * v_up;
		Vector3<double> * fp;
		

		//Wireframe frame;
		//std::vector<Vertex> * convert(std::vector<Vertex> *, std::vector<double> *, std::vector<double> *);
		//std::vector<Vertex> * clip(std::vector<Vertex> *);

	public:
		Camera(std::string, double, double, double, double, Vector3<double> *, Vector3<double> *);
		
		std::string get_name();

		Vector3<double> * getPos();
		Vector3<double> * getFocalPoint();
		Vector3<double> * getHorizontalAxis();
		Vector3<double> * getVerticalAxis();

		//void prepare_raycast(const std::vector<Group *>, const std::vector<Light * > &, const Material &);
};

//std::ostream & operator<<(std::ostream &, const Camera &);
#endif
