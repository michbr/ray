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

		bool has_frame;

		double x,y,z;
		double focal_length;

		std::vector<double> * vpn;
		std::vector<double> * v_up;
		std::vector<double> * fp;
		std::vector<Wireframe> frames;

		//Wireframe frame;
		//std::vector<Vertex> * convert(std::vector<Vertex> *, std::vector<double> *, std::vector<double> *);
		std::vector<Vertex> * clip(std::vector<Vertex> *);
		std::vector<std::vector<int> *> * image;
		std::vector<std::vector<double> *> * z_buffer;

		void bresenham (std::vector<Vertex> *);
		void fill(int, int, int, int, int);
		std::vector<int> * find_closest_face(std::vector<double> *, std::vector<double> *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light *> &, const Material &, int, double *, bool *);
		std::vector<int> * find_closest_elipse(std::vector<double> *, std::vector<double> *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light *> &, const Material &, int, double *, bool *);
		std::vector<int> * color_face_pixel(std::vector<double> *, std::vector<double> *, Face *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light * > &, const Material &, int);
		std::vector<int> * color_elipse_pixel(std::vector<double> *, std::vector<double> *, const Elipse *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light * > &, const Material &, int);
	public:
		Camera(std::string, double, double, double, double, std::vector<double> *, std::vector<double> *);
		
		bool hasFrame();
		std::string get_name();
		
		void add_frame(Wireframe *);
		void prepare_wireframe(std::vector<Group *> );
		void prepare_raycast(const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light * > &, const Material &);
		
		friend std::ostream & operator<<(std::ostream &, const Camera &);
		std::ostream & operator<<(std::ostream &);

		//void prepare_raycast(const std::vector<Group *>, const std::vector<Light * > &, const Material &);
};

std::ostream & operator<<(std::ostream &, const Camera &);
#endif
