
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

#include <iostream>

// a material object for storing material data such as diffuse color, specularity, reflectivity, etc.
class Material;

// a basic color class which stores rgb with 3 bytes
class Color;

// a basic color with an added alpha value specified with a byte
//class AlphaColor;


class Color {
	public:
		double r, g, b;	// the RGB values of the color
		
		// constructors
		Color();
		Color(int r, int g, int b);
		Color(double r, double g, double b);
		Color(const Color &col);
		
		// math operators
		Color &operator+=(const Color &other);
		//Color operator/(double scalar) const;
		//Color operator/(const Vec3 &other) const;
		Color operator/(double scalar) const;
		Color operator/(const Color &other) const;
		Color operator*(const Color &other) const;
		Color operator+(const Color &other) const;
		Color operator-(const Color &other) const;
		//Color operator==(const Vec3 &other) const;
		//Color operator!=(const Vec3 &other) const;
		
		void clamp();
};

// scalar multiply
Color operator*(const Color &col, double scalar);
Color operator*(double scalar, const Color &col);

// outputs data or state of Color
std::ostream &operator<<(std::ostream &out, const Color &col);

// reads in Color parameters from a string formatted as in a command file
std::istream &operator>>(std::istream &in, Color &col);


//class AlphaColor: public Color {
//	public:
//		double a;		// the alpha value of the color
//		
//		AlphaColor();
//		AlphaColor(int r, int g, int b);
//		AlphaColor(int r, int g, int b, int a);
//		AlphaColor(const AlphaColor &source);
//		AlphaColor(const Color &source);
//};
//std::ostream &operator<<(std::ostream &out, const AlphaColor &col);
//std::istream &operator>>(std::istream &in, AlphaColor &col);


class Material {
	public:
		Color difCol;			// the diffuse lighting color
		Color specCol;			// the specular highlight color
		Color ambCol;			// the ambient light color
		double specularity;		// the splash of the specular highlight, 0 - max double
		double refractionIndex;	// the index of refraction, 0 - 1
		double refractionAtt;	// the refraction attenuation, 0 - 1
		double alpha;			// the transparency or opacity, 0 - 1
		double reflectance;		// the reflectivity, 0 - 1
		
		Material();
		Material(const Material &source);
};
std::ostream &operator<<(std::ostream &out, const Material &mat);

#endif // RAY_MATERIAL_H