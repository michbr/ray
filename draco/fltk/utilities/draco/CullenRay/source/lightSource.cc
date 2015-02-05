
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../lightSource.h"

using namespace std;


// constructs a default light source
LightSource::LightSource() {}
		
// constructs a light source with the given position and color
LightSource::LightSource(const Vec4 &position, const Color &color): position(position), color(color) {}
		
// copies a given light source
LightSource::LightSource(const LightSource &source): position(source.position), color(source.color) {}

// outputs the data or state of the light source
ostream &operator<<(ostream &out, const LightSource &li) {
	return out << "pos" << li.position << " col" << li.color;
}

// sets a light source from a line of text as specified in a command file
istream &operator>>(istream &in, LightSource &li) {
	in >> li.position;
	in >> li.color;
	return in;
}
