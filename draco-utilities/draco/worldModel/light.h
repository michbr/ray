#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H

#include "DragonMath/dragonmath.h"
#include "face.h"

#include <vector>

class Light {
    private:
	//Vector3<double> center;
	std::vector<int> color;
	Vector3<double> center;
	double w;
    public:
	Light(double, double, double, double, int, int, int);
	double get_x() const;
	double get_y() const;
	double get_z() const;
	double get_w() const;
	const std::vector<int> * get_color() const;
	//std::vector<double> * get_center();
	bool isBlocked(Vector3<double> , const std::vector<Face *> &) const;
	const Vector3<double> * getCenter() const;
};

#endif
