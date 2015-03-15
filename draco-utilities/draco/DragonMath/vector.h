#ifndef DRAGON_MATH_VECTOR
#define DRAGON_MATH_VECTOR

#include "EXPORT.h"

#include <iostream>

template<typename T>
class Vector4;

template<typename T>
class DRACO_DRAGON_MATH_API Vector3;

template<typename T>
class Vector2 {
public:

	// constants
	static const Vector2<T> zero;
	static const Vector2<T> right;
	static const Vector2<T> left;
	static const Vector2<T> up;
	static const Vector2<T> down;

	// members
	T x, y;

	// constructors
	Vector2(T x, T y);
	Vector2(const Vector2<T> &source);
	Vector2(const Vector3<T> &source);
	Vector2(const Vector4<T> &source);

	// methods
	T magnitude() const;
	T magnitudeSquared() const;
	Vector2<T> normal() const;
	void normalize();
	Vector2<T> scale(T scalar) const;
	T dot(const Vector2<T> &other) const;

	// operators
	Vector2<T> operator/(T scalar) const;
	Vector2<T> operator/(const Vector2<T> &other) const;
	Vector2<T> operator*(const Vector2<T> &other) const;
	Vector2<T> operator+(const Vector2<T> &other) const;
	Vector2<T> operator-(const Vector2<T> &other) const;
	Vector2<T> operator-() const;
	Vector2<T> &operator+=(const Vector2<T> &other);
	Vector2<T> &operator-=(const Vector2<T> &other);
	Vector2<T> &operator*=(T scalar);
	Vector2<T> &operator/=(T scalar);
	bool operator==(const Vector2<T> &other) const;
	bool operator!=(const Vector2<T> &other) const;
	T &operator[](int index);
	T operator[](int index) const;
};

template<typename T>
DRACO_DRAGON_MATH_API Vector2<T> operator*(const Vector2<T> &vec, T scalar);

template<typename T>
DRACO_DRAGON_MATH_API Vector2<T> operator*(T scalar, const Vector2<T> &vec);

template<typename T>
DRACO_DRAGON_MATH_API std::ostream &operator<<(std::ostream &out, const Vector2<T> &vec);


template<class T>
class Vector3 {
public:

	// constants
	static const Vector3<T> zero;
	static const Vector3<T> right;
	static const Vector3<T> left;
	static const Vector3<T> up;
	static const Vector3<T> down;
	static const Vector3<T> forward;
	static const Vector3<T> back;
	
	// members
	T x, y, z;

	// constructors
	Vector3(T x, T y, T z);
	Vector3(const Vector3<T> &source);
	Vector3(const Vector4<T> &source);


	// methods
	T magnitude() const;
	T magnitudeSquared() const;
	Vector3<T> normal() const;
	void normalize();
	Vector3<T> scale(T scalar) const;
	T dot(const Vector3<T> &b) const;
	Vector3<T> cross(const Vector3<T> &b) const;

	// operators
	Vector3<T> operator/(T scalar) const;
	Vector3<T> operator/(const Vector3<T> &other) const;
	Vector3<T> operator*(const Vector3<T> &other) const;
	Vector3<T> operator+(const Vector3<T>) const;
	Vector3<T> operator-(const Vector3<T>) const;
	Vector3<T> operator-() const;
	Vector3<T> &operator+=(const Vector3<T> &other);
	Vector3<T> &operator-=(const Vector3<T> &other);
	Vector3<T> &operator*=(T scalar);
	Vector3<T> &operator/=(T scalar);
	bool operator==(const Vector3<T> &other) const;
	bool operator!=(const Vector3<T> &other) const;
	T &operator[](int index);
	T operator[](int index) const;

//	template<T> friend DRACO_DRAGON_MATH_API Vector3<T> operator*(const Vector3<T> &vec, T scalar);
//	template<T> friend DRACO_DRAGON_MATH_API Vector3<T> operator*(T scalar, const Vector3<T> &vec);
};

#ifdef DLL_EXPORT_DRACO_DRAGON_MATH
	template<typename T>
	Vector3<T> operator*(const Vector3<T> &vec, T scalar) {
		return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
	}

	template<typename T>
	Vector3<T> operator*(T scalar, const Vector3<T> &vec) {
		return Vector3<T>(vec.x *scalar, vec.y *scalar, vec.z *scalar);
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &out, const Vector3<T> &vec) {
		return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}
#else
	template<typename T>
	DRACO_DRAGON_MATH_API Vector3<T> operator*(const Vector3<T> &vec, T scalar);

	template<typename T>
	DRACO_DRAGON_MATH_API Vector3<T> operator*(T scalar, const Vector3<T> &vec);

	template<typename T>
	DRACO_DRAGON_MATH_API std::ostream &operator<<(std::ostream &out, const Vector3<T> &vec);
#endif // DLL_EXPORT_DRACO_DRAGON_MATH

template<typename T>
class Vector4 {
public:

	// constants
	static const Vector4<T> zero;
	static const Vector4<T> right;
	static const Vector4<T> left;
	static const Vector4<T> up;
	static const Vector4<T> down;
	static const Vector4<T> forward;
	static const Vector4<T> back;

	// members
	T x, y, z, w;

	// constructors
	Vector4(T x, T y, T z);
	Vector4(T x, T y, T z, T w);
	Vector4(const Vector3<T> &source);
	Vector4(const Vector4<T> &source);

	// methods
	T magnitude() const;
	T magnitudeSquared() const;
	Vector4<T> normal() const;
	void normalize();
	Vector4<T> scale(T scalar) const;
	T dot(const Vector4<T> &other) const;
	Vector4<T> cross(const Vector4<T> &other) const;

	// operators
	Vector4<T> operator/(T scalar) const;
	Vector4<T> operator/(const Vector4<T> &other) const;
	Vector4<T> operator*(const Vector4<T> &other) const;
	Vector4<T> operator+(const Vector4<T> &other) const;
	Vector4<T> operator-(const Vector4<T> &other) const;
	Vector4<T> operator-() const;
	Vector4<T> &operator+=(const Vector4<T> &other);
	Vector4<T> &operator-=(const Vector4<T> &other);
	Vector4<T> &operator*=(T scalar);
	Vector4<T> &operator/=(T scalar);
	bool operator==(const Vector4<T> &other) const;
	bool operator!=(const Vector4<T> &other) const;
	T &operator[](int index);
	T operator[](int index) const;
};

template<typename T>
DRACO_DRAGON_MATH_API Vector4<T> operator*(const Vector4<T> &vec, T scalar);

template<typename T>
DRACO_DRAGON_MATH_API Vector4<T> operator*(T scalar, const Vector4<T> &vec);

template<typename T>
DRACO_DRAGON_MATH_API std::ostream &operator<<(std::ostream &out, const Vector4<T> &vec);


#endif
