
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../material.h"

using namespace std;



//////////////
// Material //
//////////////

Material::Material(): specCol(64, 64, 64), ambCol(32, 32, 32), specularity(1), refractionIndex(1), refractionAtt(1), alpha(1), reflectance(0) {}
Material::Material(const Material &source):
	difCol(source.difCol),
	specCol(source.specCol),
	ambCol(source.ambCol),
	specularity(source.specularity),
	refractionIndex(source.refractionIndex),
	refractionAtt(source.refractionAtt),
	alpha(source.alpha),
	reflectance(source.reflectance) {}

ostream &operator<<(ostream &out, const Material &mat) {
	return out << "dif: " << mat.difCol << ", spec: " << mat.specCol << ", amb: " << mat.ambCol << ", specularity: " << mat.specularity;
}


///////////
// Color //
///////////

const double MAX_COLOR = 255;

double clampVal(double val) {
	return max(min(val, 1.0), 0.0);
}

Color::Color(): Color(0, 0, 0) {}
Color::Color(int r, int g, int b): r(r/MAX_COLOR), g(g/MAX_COLOR), b(b/MAX_COLOR) {}
Color::Color(double r, double g, double b): r(r), g(g), b(b) {}
Color::Color(const Color &source): Color(source.r, source.g, source.b) {}

Color &Color::operator+=(const Color &other) {
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}
Color Color::operator/(double scalar) const {
	return Color(r /scalar, g /scalar, b /scalar);
}
Color Color::operator/(const Color &other) const {
	return Color(r /other.r, g /other.g, b /other.b);
}
Color Color::operator*(const Color &other) const {
	return Color(r *other.r, g *other.g, b *other.b);
}
Color Color::operator+(const Color &other) const {
	return Color(r +other.r, g +other.g, b +other.b);
}
Color Color::operator-(const Color &other) const {
	return Color(r -other.r, g -other.g, b -other.b);
}

Color operator*(const Color &col, double scalar) {
	return Color(col.r *scalar, col.g *scalar, col.b *scalar);
}
Color operator*(double scalar, const Color &col) {
	return Color(col.r *scalar, col.g *scalar, col.b *scalar);
}

void Color::clamp() {
	r = clampVal(r);
	g = clampVal(g);
	b = clampVal(b);
}

ostream &operator<<(ostream &out, const Color &col) {
	return out << (int)(clampVal(col.r) *MAX_COLOR) << " " << (int)(clampVal(col.g) *MAX_COLOR) << " " << (int)(clampVal(col.b) *MAX_COLOR);
}

istream &operator>>(istream &in, Color &col) {
	int tempCol;
	in >> tempCol;
	col.r = tempCol /MAX_COLOR;
	in >> tempCol;
	col.g = tempCol /MAX_COLOR;
	in >> tempCol;
	col.b = tempCol /MAX_COLOR;
	return in;
}


////////////////
// AlphaColor //
////////////////

//AlphaColor::AlphaColor(): AlphaColor(1, 1, 1) {}
//AlphaColor::AlphaColor(int r, int g, int b): AlphaColor(r, g, b, a) {}
//AlphaColor::AlphaColor(int r, int g, int b, int a): Color(r, g, b), a(a) {}
//AlphaColor::AlphaColor(const AlphaColor &source): Color(source), a(source.a) {}
//AlphaColor::AlphaColor(const Color &source): Color(source), a(1) {}
//
//ostream &operator<<(ostream &out, const AlphaColor &col) {
//	return out << '(' << (int)col.r << ", " << (int)col.g << ", " << (int)col.b << ", " << (int)col.a << ")";
//}
//
//istream &operator>>(istream &in, AlphaColor &col) {
//	int tempCol;
//	in >> tempCol;
//	col.r = tempCol;
//	in >> tempCol;
//	col.g = tempCol;
//	in >> tempCol;
//	col.b = tempCol;
//	in >> tempCol;
//	col.a = tempCol;
//	return in;
//}
