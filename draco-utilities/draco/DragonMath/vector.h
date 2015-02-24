#ifndef DRAGON_MATH_VECTOR
#define DRAGON_MATH_VECTOR

#include <iostream>

template<class T>
class Vector4;

template<class T>
class Vector3;

template<class T>
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
	T megnitude() const;
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

template<class T>
Vector2<T> operator*(const Vector2<T> &vec, T scalar);

template<class T>
Vector2<T> operator*(T scalar, const Vector2<T> &vec);

template<class T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &vec);

/*********
Items missing from Vector3
-Default constructor (do we really need one?)
-Static pre-initialized versions?
-magnitude renamed to length?
-lengthSquared???
*********/

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
//	Vector3<T> findPerpendicular() const;
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
};


template<class T>
Vector3<T> operator*(const Vector3<T> &vec, T scalar);

template<class T>
Vector3<T> operator*(T scalar, const Vector3<T> &vec);

template<class T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &vec);


template<class T>
class Vector4 {
public:

	// constants
	static const Vector4<T> zeroAbsolute;
	static const Vector4<T> zero;
	static const Vector4<T> right;
	static const Vector4<T> left;
	static const Vector4<T> up;
	static const Vector4<T> down;
	static const Vector4<T> forward;
	static const Vector4<T> bacl;

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
	T dot(const Vector4<T> &other) const;
	Vector4<T> cross(const Vector4<T> &other) const;

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

template<class T>
Vector4<T> operator*(const Vector4<T> &vec, T scalar);

template<class T>
Vector4<T> operator*(T scalar, const Vector4<T> &vec);

template<class T>
std::ostream &operator<<(std::ostream &out, const Vector4<T> &vec);


#endif
