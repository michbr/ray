
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_IMAGE_H
#define RAY_IMAGE_H

#include "math.h"
#include "material.h"


class Image {
	public:
		
		Image(size_t width, size_t height);
		Image(const Vec2 &size);
		~Image();
		
		void resize(size_t width, size_t height);
		void resize(const Vec2 &newSize);
		void set(size_t x, size_t y, const Color &pixel);
		void set(size_t x, size_t y, double depth);
		
		// this method antialiases the image using the depth information.  It is extremeley experimental
		void antialias(double depthWeight=0.1);
		
		const Color &get(size_t x, size_t y) const;
		double getDepth(size_t x, size_t y) const;
		
		Vec2 getSize() const;
		
	private:
		size_t width, height;
		Vec2 size;
		Color *pixels;
		double *depths;
};

#endif // RAY_IMAGE_H