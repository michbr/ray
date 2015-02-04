
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "image.h"

#include <cstring>


using namespace std;


Image::Image(size_t width, size_t height): pixels(NULL), depths(NULL) {
	resize(width, height);
}
Image::Image(const Vec2 &size): Image(size.x, size.y) {}
Image::~Image() {
	if (pixels != NULL)
		free(pixels);
	if (depths != NULL)
		free(depths);
}

void Image::resize(size_t width, size_t height) {
	if (pixels != NULL)
		free(pixels);
	if (depths != NULL)
		free(depths);
	this->width = width;
	this->height = height;
	pixels = (Color*) malloc(width *height *sizeof(Color));
	depths = (double*) malloc(width *height *sizeof(double));
}
void Image::resize(const Vec2 &newSize) {
	resize(newSize.x, newSize.y);
}

void Image::set(size_t x, size_t y, const Color &pixel) {
	pixels[x +y *width] = pixel;
}
void Image::set(size_t x, size_t y, double depth) {
	depths[x +y *width] = depth;
}

void Image::antialias(double depthWeight) {
	Color *oldPixels = (Color*) malloc(width *height *sizeof(Color));
	memcpy(oldPixels, pixels, width *height *sizeof(Color));
	for (size_t x=1; x<width -1; ++x) {
		for (size_t y=1; y<height -1; ++y) {
			double higherCount = 0;
			Color col(0, 0, 0);
			bool horiDiff = false;
			bool vertDiff = false;
			double curDepth = depths[x +y *width];
			if (depths[(x -1) +y *width] < curDepth -0.1 /depthWeight) {
				double blend = min(0.5, (curDepth -depths[(x -1) +y *width]) *depthWeight);
				col += oldPixels[x -1 +y *width] *blend;
				horiDiff = true;
				higherCount += blend;
			}
			if (depths[(x +1) +y *width] < curDepth -0.1 /depthWeight) {
				double blend = min(0.5, (curDepth -depths[(x +1) +y *width]) *depthWeight);
				col += oldPixels[x +1 +y *width] *blend;
				horiDiff = true;
				higherCount += blend;
			}
			if (depths[x +(y -1) *width] < curDepth -0.1 /depthWeight) {
				double blend = min(0.5, (curDepth -depths[x +(y -1) *width]) *depthWeight);
				col += oldPixels[x +(y -1) *width] *blend;
				vertDiff = true;
				higherCount += blend;
			}
			if (depths[x +(y +1) *width] < curDepth -0.1 /depthWeight) {
				double blend = min(0.5, (curDepth -depths[x +(y +1) *width]) *depthWeight);
				col += oldPixels[x +(y +1) *width] *blend;
				vertDiff = true;
				higherCount += blend;
			}
			if (vertDiff && horiDiff) {
				col = col /higherCount;
				Color pixel = oldPixels[x +y *width];
				pixels[x +y *width] = Color((pixel.r +col.r) /2, (pixel.g +col.g) /2, (pixel.b +col.b) /2);
			}
		}
	}
	free(oldPixels);
}

const Color &Image::get(size_t x, size_t y) const {
	return pixels[x +y *width];
}
double Image::getDepth(size_t x, size_t y) const {
	return depths[x +y *width];
}

Vec2 Image::getSize() const {
	return Vec2(width, height);
}
