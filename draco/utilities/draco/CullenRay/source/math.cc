
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../math.h"
#include <cmath>


using namespace std;


//////////////
// Vector 2 //
//////////////

// constructors
Vec2::Vec2(): Vec2(0, 0) {}
Vec2::Vec2(double x, double y): x(x), y(y) {}
Vec2::Vec2(const Vec2 &source): Vec2(source.x, source.y) {}
Vec2::Vec2(const Vec3 &source): Vec2(source.x, source.y) {}
Vec2::Vec2(const Vec4 &source): Vec2(source.x, source.y) {}

// methods
double Vec2::length() const {
	return sqrt(x*x +y*y);
}
double Vec2::lengthSquared() const {
	return x*x +y*y;
}
double Vec2::distance(const Vec2 &other) const {
	Vec2 diff = Vec2(x -other.x, y -other.y);
	return diff.length();
}
double Vec2::dot(const Vec2 &other) const {
	return x *other.x +y *other.y;
}
Vec2 Vec2::normal() const {
	double l = length();
	return Vec2(x /l, y /l);
}
void Vec2::normalize() {
	double l = length();
	x /= l; y /= l;
}

// operators
Vec2 Vec2::operator/(double scalar) const {
	return Vec2(x /scalar, y /scalar);
}
Vec2 Vec2::operator/(const Vec2 &other) const {
	return Vec2(x /other.x, y /other.y);
}
Vec2 Vec2::operator*(const Vec2 &other) const {
	return Vec2(x *other.x, y *other.y);
}
Vec2 Vec2::operator+(const Vec2 &other) const {
	return Vec2(x +other.x, y +other.y);
}
Vec2 Vec2::operator-(const Vec2 &other) const {
	return Vec2(x -other.x, y -other.y);
}
Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}
bool Vec2::operator==(const Vec2 &other) const {
	return x == other.x && y == other.y;
}
bool Vec2::operator!=(const Vec2 &other) const {
	return !(*this == other);
}
Vec2 operator*(const Vec2 &vec, double scalar) {
	return Vec2(vec.x *scalar, vec.y *scalar);
}
Vec2 operator*(double scalar, const Vec2 &vec) {
	return Vec2(vec.x *scalar, vec.y *scalar);
}
Vec2 &Vec2::operator+=(const Vec2 &other) {
	x += other.x; y += other.y;
	return *this;
}
Vec2 &Vec2::operator-=(const Vec2 &other) {
        x -= other.x; y -= other.y;
        return *this;
}
Vec2 &Vec2::operator*=(double scalar) {
        x *= scalar; y *= scalar;
        return *this;
}
Vec2 &Vec2::operator/=(double scalar) {
        x /= scalar; y /= scalar;
        return *this;
}

// output/input
ostream &operator<<(ostream &out, const Vec2 &vec) {
	return out << '(' << vec.x << ", " << vec.y << ")";
}

istream &operator>>(istream &in, Vec2 &vec) {
	in >> vec.x;
	in >> vec.y;
	return in;
}

// constants
const Vec2 Vec2::zero(0, 0);
const Vec2 Vec2::one(1, 1);
const Vec2 Vec2::right(1, 0);
const Vec2 Vec2::up(0, 1);


//////////////
// Vector 3 //
//////////////

// constructors
Vec3::Vec3(): Vec3(0, 0, 0) {}
Vec3::Vec3(double x, double y, double z): x(x), y(y), z(z) {}
Vec3::Vec3(const Vec3 &source): x(source.x), y(source.y), z(source.z) {}
Vec3::Vec3(const Vec4 &source): x(source.x), y(source.y), z(source.z) {}

// methods
double Vec3::length() const {
	return sqrt(x*x +y*y +z*z);
}
double Vec3::lengthSquared() const {
	return x*x +y*y +z*z;
}
double Vec3::distance(const Vec3 &other) const {
	Vec3 diff = Vec3(x -other.x, y -other.y, z -other.z);
	return diff.length();
}
double Vec3::dot(const Vec3 &other) const {
	return x *other.x +y *other.y +z *other.z;
}
Vec3 Vec3::normal() const {
	double l = length();
	return Vec3(x /l, y /l, z /l);
}
void Vec3::normalize() {
        double l = length();
        x /= l; y /= l; z /= l;
}
Vec3 Vec3::cross(const Vec3 &other) const {
	return Vec3(y *other.z -z *other.y,
				z *other.x -x *other.z,
				x *other.y -y *other.x);
}

// operators
Vec3 Vec3::operator/(double scalar) const {
	return Vec3(x /scalar, y /scalar, z /scalar);
}
Vec3 Vec3::operator/(const Vec3 &other) const {
	return Vec3(x /other.x, y /other.y, z /other.z);
}
Vec3 Vec3::operator*(const Vec3 &other) const {
	return Vec3(x *other.x, y *other.y, z *other.z);
}
Vec3 Vec3::operator+(const Vec3 &other) const {
	return Vec3(x +other.x, y +other.y, z +other.z);
}
Vec3 Vec3::operator-(const Vec3 &other) const {
	return Vec3(x -other.x, y -other.y, z -other.z);
}
Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}
bool Vec3::operator==(const Vec3 &other) const {
	return x == other.x && y == other.y && z == other.z;
}
bool Vec3::operator!=(const Vec3 &other) const {
	return !(*this == other);
}
Vec3 operator*(const Vec3 &vec, double scalar) {
	return Vec3(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
Vec3 operator*(double scalar, const Vec3 &vec) {
	return Vec3(vec.x *scalar, vec.y *scalar, vec.z *scalar);
}
Vec3 &Vec3::operator+=(const Vec3 &other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
}
Vec3 &Vec3::operator-=(const Vec3 &other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
}
Vec3 &Vec3::operator*=(double scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
}
Vec3 &Vec3::operator/=(double scalar) {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
}

// output/input
ostream &operator<<(ostream &out, const Vec3 &vec) {
	return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

istream &operator>>(istream &in, Vec3 &vec) {
	in >> vec.x;
	in >> vec.y;
	in >> vec.z;
	return in;
}

// constants
const Vec3 Vec3::zero(0, 0, 0);
const Vec3 Vec3::one(1, 1, 1);
const Vec3 Vec3::right(1, 0, 0);
const Vec3 Vec3::up(0, 1, 0);
const Vec3 Vec3::forward(0, 0, 1);


//////////////
// Vector 4 //
//////////////

// constructors
Vec4::Vec4(): Vec4(0, 0, 0) {}
Vec4::Vec4(double x, double y, double z): Vec4(x, y, z, 1) {}
Vec4::Vec4(double x, double y, double z, double w): x(x), y(y), z(z), w(w) {}
Vec4::Vec4(const Vec3 &source): Vec4(source.x, source.y, source.z) {}
Vec4::Vec4(const Vec4 &source): Vec4(source.x, source.y, source.z, source.w) {}

// methods
double Vec4::length() const {
	return sqrt(x*x +y*y +z*z);
}
double Vec4::lengthSquared() const {
	return x*x +y*y +z*z;
}
double Vec4::distance(const Vec4 &other) const {
	Vec4 diff = Vec4(x -other.x, y -other.y, z -other.z);
	return diff.length();
}
double Vec4::dot(const Vec4 &other) const {
	return x *other.x +y *other.y +z *other.z;
}
Vec4 Vec4::normal() const {
	double l = length();
	return Vec4(x /l, y /l, z /l, w);
}
void Vec4::normalize() {
        double l = length();
        x /= l; y /= l; z /= l;
}
Vec4 Vec4::cross(const Vec4 &other) const {
	return Vec4(y *other.z -z *other.y,
				z *other.x -x *other.z,
				x *other.y -y *other.x,
				w);
}

// operators
Vec4 Vec4::operator/(double scalar) const {
	return Vec4(x /scalar, y /scalar, z /scalar, w);
}
Vec4 Vec4::operator/(const Vec4 &other) const {
	return Vec4(x /other.x, y /other.y, z /other.z, w /other.w);
}
Vec4 Vec4::operator*(const Vec4 &other) const {
	return Vec4(x *other.x, y *other.y, z *other.z, w *other.w);
}
Vec4 Vec4::operator+(const Vec4 &other) const {
	return Vec4(x +other.x, y +other.y, z +other.z, w);
}
Vec4 Vec4::operator-(const Vec4 &other) const {
	return Vec4(x -other.x, y -other.y, z -other.z, w);
}
Vec4 Vec4::operator-() const {
	return Vec4(-x, -y, -z, w);
}
bool Vec4::operator==(const Vec4 &other) const {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}
bool Vec4::operator!=(const Vec4 &other) const {
	return !(*this == other);
}
Vec4 operator*(const Vec4 &vec, double scalar) {
	return Vec4(vec.x *scalar, vec.y *scalar, vec.z *scalar, vec.w);
}
Vec4 operator*(double scalar, const Vec4 &vec) {
	return Vec4(vec.x *scalar, vec.y *scalar, vec.z *scalar, vec.w);
}
Vec4 &Vec4::operator+=(const Vec4 &other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
}
Vec4 &Vec4::operator-=(const Vec4 &other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
}
Vec4 &Vec4::operator*=(double scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
}
Vec4 &Vec4::operator/=(double scalar) {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
}

// output/input
ostream &operator<<(ostream &out, const Vec4 &vec) {
	return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}

istream &operator>>(istream &in, Vec4 &vec) {
	in >> vec.x;
	in >> vec.y;
	in >> vec.z;
	if (in.eof()) return in;
	in >> vec.w;
	return in;
}

// constants
const Vec4 Vec4::zeroAbsolute(0, 0, 0, 0);
const Vec4 Vec4::zero(0, 0, 0);
const Vec4 Vec4::one(1, 1, 1);
const Vec4 Vec4::right(1, 0, 0);
const Vec4 Vec4::up(0, 1, 0);
const Vec4 Vec4::forward(0, 0, 1);


//////////
// Ray3 //
//////////

// constructors
Ray3::Ray3(): position(Vec3()), vector(Vec3()) {}
Ray3::Ray3(const Vec3 &position, const Vec3 &vector): position(position), vector(vector) {}
Ray3::Ray3(const Ray3 &source): position(source.position), vector(source.vector) {}
