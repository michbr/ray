
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_IMAGE_H
#define RAY_IMAGE_H

#include "dragonmath.h"
#include "material.h"


class Image {
	public:
		
		Image(size_t width, size_t height);
		Image(const Vector2<double> &size);
		~Image();
		
		void resize(size_t width, size_t height);
		void resize(const Vector2<double> &newSize);
		void set(size_t x, size_t y, const Color &pixel);
		void set(size_t x, size_t y, double depth);
		
		// this method antialiases the image using the depth information.  It is extremeley experimental
		void antialias(double depthWeight=0.1);
		
		const Color &get(size_t x, size_t y) const;
		double getDepth(size_t x, size_t y) const;
		
		Vector2<double> getSize() const;
		
	private:
		size_t width, height;
		//Vector2<double> size;
		Color *pixels;
		double *depths;
};

#endif // RAY_IMAGE_H
