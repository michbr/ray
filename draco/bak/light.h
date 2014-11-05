#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H

#include "vertex.h"
#include "face.h"
#include "elipse.h"

#include <vector>

class Light {
    private:
	Vertex center;
	std::vector<int> color;
	std::vector<double> center_point;
	void set_center();
    public:
	Light(double, double, double, double, int, int, int);
	double get_x() const;
	double get_y() const;
	double get_z() const;
	double get_w() const;
	const std::vector<int> * get_color() const;
	//std::vector<double> * get_center();
	bool is_blocked(std::vector<double> *, const std::vector<Face *> &, const std::vector<Elipse *> &);
	const std::vector<double> * get_center() const;
};

#endif
