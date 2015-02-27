
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "dragonmath.h"
#include "material.h"

#include <iostream>


class LightSource {
	public:
		Vector4<double> position;		// the position of the light source.  w specifies inifite distance if 0
		Color color;		// the color of the light source
		
		// constructs a default light source
		LightSource();
		
		// constructs a light source with the given position and color
		LightSource(const Vector4<double> &position, const Color &color);
		
		// copies a given light source
		LightSource(const LightSource &source);
		
};

// outputs the data or state of the light source
std::ostream &operator<<(std::ostream &out, const LightSource &li);

// sets a light source from a line of text as specified in a command file
std::istream &operator>>(std::istream &in, LightSource &li);

#endif //LIGHT_SOURCE_H
