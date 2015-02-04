
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_MATH_H
#define RAY_MATH_H

#include <iostream>

class Vec2;
class Vec3;
class Vec4;
class Ray;


//////////////
// Vector 2 //
//////////////

class Vec2 {
	public:
		
		// constants
		static const Vec2 zero;
		static const Vec2 one;
		static const Vec2 right;
		static const Vec2 up;
		
		// memebers
		double x, y;
		
		// constructors
		Vec2();
		Vec2(double x, double y);
		Vec2(const Vec2 &source);
		Vec2(const Vec3 &source);
		Vec2(const Vec4 &source);
		
		// methods
		double length() const;
		double lengthSquared() const;
		double distance(const Vec2 &other) const;
		double dot(const Vec2 &other) const;
		Vec2 normal() const;
		void normalize();
		Vec2 operator/(double scalar) const;
		Vec2 operator/(const Vec2 &other) const;
		Vec2 operator*(const Vec2 &other) const;
		Vec2 operator+(const Vec2 &other) const;
		Vec2 operator-(const Vec2 &other) const;
		Vec2 operator-() const;
                Vec2 &operator+=(const Vec2 &other);
                Vec2 &operator-=(const Vec2 &other);
                Vec2 &operator*=(double scalar);
                Vec2 &operator/=(double scalar);
		bool operator==(const Vec2 &other) const;
		bool operator!=(const Vec2 &other) const;
};

Vec2 operator*(const Vec2 &vec, double scalar);
Vec2 operator*(double scalar, const Vec2 &vec);
std::ostream &operator<<(std::ostream &out, const Vec2 &vec);
std::istream &operator>>(std::istream &in, Vec2 &vec);

//////////////
// Vector 3 //
//////////////

class Vec3 {
	public:
		
		// constants
		static const Vec3 zero;
		static const Vec3 one;
		static const Vec3 right;
		static const Vec3 up;
		static const Vec3 forward;
		
		// memebers
		double x, y, z;
		
		// constructors
		Vec3();
		Vec3(double x, double y, double z);
		Vec3(const Vec3 &source);
		Vec3(const Vec4 &source);
		
		// methods
		double length() const;
		double lengthSquared() const;
		double distance(const Vec3 &other) const;
		double dot(const Vec3 &other) const;
		Vec3 normal() const;
		void normalize();
		Vec3 cross(const Vec3 &other) const;
		Vec3 operator/(double scalar) const;
		Vec3 operator/(const Vec3 &other) const;
		Vec3 operator*(const Vec3 &other) const;
		Vec3 operator+(const Vec3 &other) const;
		Vec3 operator-(const Vec3 &other) const;
		Vec3 operator-() const;
		Vec3 &operator+=(const Vec3 &other);
		Vec3 &operator-=(const Vec3 &other);
		Vec3 &operator*=(double scalar);
		Vec3 &operator/=(double scalar);
		bool operator==(const Vec3 &other) const;
		bool operator!=(const Vec3 &other) const;
};

Vec3 operator*(const Vec3 &vec, double scalar);
Vec3 operator*(double scalar, const Vec3 &vec);
std::ostream &operator<<(std::ostream &out, const Vec3 &vec);
std::istream &operator>>(std::istream &in, Vec3 &vec);



//////////////
// Vector 4 //
//////////////

class Vec4 {
	public:
		
		// constants
		static const Vec4 zeroAbsolute;
		static const Vec4 zero;
		static const Vec4 one;
		static const Vec4 right;
		static const Vec4 up;
		static const Vec4 forward;
		
		// memebers
		double x, y, z, w;
		
		// constructors
		Vec4();
		Vec4(double x, double y, double z);
		Vec4(double x, double y, double z, double w);
		Vec4(const Vec3 &source);
		Vec4(const Vec4 &source);
		
		// methods
		double length() const;
		double lengthSquared() const;
		double distance(const Vec4 &other) const;
		double dot(const Vec4 &other) const;
		Vec4 normal() const;
		void normalize();
		Vec4 cross(const Vec4 &other) const;
		//Vec4 &operator+=(const Vec4 &other);
		//Vec4 &operator-=(const Vec4 &other);
		//Vec4 &operator*=(double scalar);
		Vec4 operator/(double scalar) const;
		Vec4 operator/(const Vec4 &other) const;
		Vec4 operator*(const Vec4 &other) const;
		Vec4 operator+(const Vec4 &other) const;
		Vec4 operator-(const Vec4 &other) const;
		Vec4 operator-() const;
                Vec4 &operator+=(const Vec4 &other);
                Vec4 &operator-=(const Vec4 &other);
                Vec4 &operator*=(double scalar);
                Vec4 &operator/=(double scalar);
		bool operator==(const Vec4 &other) const;
		bool operator!=(const Vec4 &other) const;
};

Vec4 operator*(const Vec4 &vec, double scalar);
Vec4 operator*(double scalar, const Vec4 &vec);
std::ostream &operator<<(std::ostream &out, const Vec4 &vec);
std::istream &operator>>(std::istream &in, Vec4 &vec);


//////////
// Ray3 //
//////////

class Ray3 {
	public:
		Vec3 position, vector;
		
		Ray3();
		Ray3(const Vec3 &position, const Vec3 &vector);
		Ray3(const Ray3 &source);
};

#endif // RAY_MATH_H
