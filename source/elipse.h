#ifndef ELIPSE_OBJECT_H
#define ELIPSE_OBJECT_H

#include "vertex.h"

class Elipse {
	private:
		std::string material;
		double radius_x, radius_y, radius_z;
		int vertex_number;
		Vertex center;
		std::vector<double> center_point;
		void set_center();
		//bool hit;
	public:
		//Elipse(double, double, double, double, double, double, double);
		Elipse(std::string, Vertex, double, double, double);
		std::vector<double> * intersect(const std::vector<double> *, const std::vector<double> *) const;
		std::string get_material() const;
		bool is_inside(const std::vector<double> *) const;
		std::vector<double> * get_normal(std::vector<double> *) const;
		const std::vector<double> * get_center() const;
		double get_radius() const;
};
#endif
