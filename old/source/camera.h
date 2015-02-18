#ifndef CAMERA_OBJECT_H
#define CAMERA_OBJECT_H

#include "wireframe.h"
#include "light.h"
#include "material.h"
#include "group.h"

#include <string>
#include <vector>

class Camera {
	private:
		std::string name;

		double x,y,z;
		double focal_length;

		std::vector<double> * vpn;
		std::vector<double> * v_up;
		std::vector<double> * fp;
		

		//Wireframe frame;
		//std::vector<Vertex> * convert(std::vector<Vertex> *, std::vector<double> *, std::vector<double> *);
		//std::vector<Vertex> * clip(std::vector<Vertex> *);

	public:
		Camera(std::string, double, double, double, double, std::vector<double> *, std::vector<double> *);
		
		std::string get_name();

		std::vector<double> * getPos();
		std::vector<double> * getFocalPoint();
		std::vector<double> * getHorizontalAxis();
		std::vector<double> * getVerticalAxis();

		//void prepare_raycast(const std::vector<Group *>, const std::vector<Light * > &, const Material &);
};

//std::ostream & operator<<(std::ostream &, const Camera &);
#endif
