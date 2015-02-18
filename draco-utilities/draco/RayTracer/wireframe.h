#ifndef WIREFRAME_OBJECT_H
#define WIREFRAME_OBJECT_H

#include <string>
#include <vector>

class Wireframe {
	private:
		int r_depth;
		double min_x,min_y,max_x, max_y;
		std::string name;
	public:
		Wireframe(std::string, double, double, double, double, int);
		double get_minx() const;
		double get_miny() const;
		double get_maxx() const;
		double get_maxy() const;
		
		int get_depth();
};
#endif
