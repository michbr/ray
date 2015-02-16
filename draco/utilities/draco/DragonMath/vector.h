#ifndef DRAGON_MATH_VECTOR
#define DRAGON_MATH_VECTOR

#include <iostream>

template <class T> class Vector4;
template <class T> class Vector3;

template <class T>
class Vector2 {
        public:

                // constants
                static const Vector2<T> zero;
                static const Vector2<T> one;
                static const Vector2<T> right;
                static const Vector2<T> up;

                // memebers
                T x, y;

                // constructors
                Vector2();
                Vector2(double x, double y);
                Vector2(const Vector2<T> &source);
                Vector2(const Vector3<T> &source);
                Vector2(const Vector4<T> &source);

                // methods
                double length() const;
                double lengthSquared() const;
                double distance(const Vector2<T> &other) const;
                double dot(const Vector2<T> &other) const;
                Vector2<T> normal() const;
                void normalize();
                Vector2<T> operator/(double scalar) const;
                Vector2<T> operator/(const Vector2<T> &other) const;
                Vector2<T> operator*(const Vector2<T> &other) const;
                Vector2<T> operator+(const Vector2<T> &other) const;
                Vector2<T> operator-(const Vector2<T> &other) const;
                Vector2<T> operator-() const;
                Vector2<T> &operator+=(const Vector2<T> &other);
                Vector2<T> &operator-=(const Vector2<T> &other);
                Vector2<T> &operator*=(double scalar);
                Vector2<T> &operator/=(double scalar);
                bool operator==(const Vector2<T> &other) const;
                bool operator!=(const Vector2<T> &other) const;
};

template <class T>
Vector2<T> operator*(const Vector2<T> &vec, double scalar);
template <class T>
Vector2<T> operator*(double scalar, const Vector2<T> &vec);
template <class T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &vec);
template <class T>
std::istream &operator>>(std::istream &in, Vector2<T> &vec);

/*********
	Items missing from Vector3
		-Default constructor (do we really need one?)
		-Static pre-initialized versions?
		-magnitude renamed to length?
		-lengthSquared???
*********/

template <class T>
class Vector3 {
        public:
		// constants
		static const Vector3<T> zero;
	
		// member variables
                T x, y, z;

		// constructors
		Vector3();
                Vector3(T x, T y, T z);
		Vector3(const Vector3<T> &source);
		Vector3(const Vector4<T> &source);

		// methods
                Vector3 cross(Vector3 b);
                T magnitude();

		Vector3 normal() const;
                void normalize();
		
		
                Vector3 cross(const Vector3 & b) const;
                Vector3 scale (T scalar) const;

                //static void equal(const Vector3 & a, const Vector3 & b);
                Vector3 findPerpendicular() const;

                T dot(const Vector3 & b) const;

                Vector3 operator/(double scalar) const;
                Vector3 operator/(const Vector3 &other) const;
                Vector3 operator*(const Vector3 &other) const;
                Vector3 operator+(const Vector3) const;
                Vector3 operator-(const Vector3) const;
                Vector3 operator-() const;
                Vector3 &operator+=(const Vector3 &other);
                Vector3 &operator-=(const Vector3 &other);
                Vector3 &operator*=(double scalar);
                Vector3 &operator/=(double scalar);
                bool operator==(const Vector3 &other) const;
                bool operator!=(const Vector3 &other) const;


                T& operator[](int index);
                T operator[](int index) const;

                friend std::ostream & operator<<(std::ostream& os, const Vector3<T> & a) {
                        os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
                        return os;
                }
};


template <class T>
Vector3<T> operator*(const Vector3<T> &vec, double scalar);
template <class T>
Vector3<T> operator*(double scalar, const Vector3<T> &vec);
template <class T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &vec);
template <class T>
std::istream &operator>>(std::istream &in, Vector3<T> &vec);


template <class T>
class Vector4 {
        public:
                
                // constants
                static const Vector4<T> zeroAbsolute;
                static const Vector4<T> zero;
                static const Vector4<T> one;
                static const Vector4<T> right;
                static const Vector4<T> up;
                static const Vector4<T> forward;
                
                // members
                T x, y, z, w;
                
                // constructors
                Vector4();
                Vector4(T x, T y, T z);
                Vector4(T x, T y, T z, T w);
                Vector4(const Vector3<T> &source);
                Vector4(const Vector4 &source);

                // methods
                T& operator[](int index);
                T operator[](int index) const;
                T length() const;
                T lengthSquared() const;
                T distance(const Vector4 &other) const;
                T dot(const Vector4 &other) const;
                Vector4 normal() const;
                void normalize();
                Vector4 cross(const Vector4 &other) const;
                Vector4 operator/(T scalar) const;
                Vector4 operator/(const Vector4 &other) const;
                Vector4 operator*(const Vector4 &other) const;
                Vector4 operator+(const Vector4 &other) const;
                Vector4 operator-(const Vector4 &other) const;
                Vector4 operator-() const;
                Vector4 &operator+=(const Vector4 &other);
                Vector4 &operator-=(const Vector4 &other);
                Vector4 &operator*=(T scalar);
                Vector4 &operator/=(T scalar);
                bool operator==(const Vector4 &other) const;
                bool operator!=(const Vector4 &other) const;
};

template <class T>
Vector4<T> operator*(const Vector4<T> &vec, T scalar);
template <class T>
Vector4<T> operator*(T scalar, const Vector4<T> &vec);
template <class T>
std::ostream &operator<<(std::ostream &out, const Vector4<T> &vec);
template <class T>
std::istream &operator>>(std::istream &in, Vector4<T> &vec);



#endif
