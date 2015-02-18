#include "image.h"

Image::Image(size_t width, size_t height) {
	w = width;
	h = height;
	image = new unsigned char[height*width*3];/*new unsigned char**[height];
	for (size_t i = 0; i < height; i++) {
		image[i] = new unsigned char*[width];	
		for (size_t j = 0; j < width; j++) {
			image[i][j] = new unsigned char[3];
		}
	}	*/
}

size_t Image::getWidth() {
	return w;
}

size_t Image::getHeight() {
	return h;
}

const unsigned char * Image::getRawImage() {
	return (const unsigned char *)image;
}

unsigned char Image::Color::r() {
	return color[0];
}

unsigned char Image::Color::g() {
	return color[1];
}

unsigned char Image::Color::b() {
	return color[2];
}

void Image::Color::r(unsigned char c) {
	color[0] = c;
}
void Image::Color::g(unsigned char c) {
	color[1] = c;
}
void Image::Color::b(unsigned char c) {
	color[2] = c;
}

const Image::Color Image::operator()(int x, int y) const {
	Color c;
	c.color = &image[3*(y*w + x)];
	return c;
}

Image::Color Image::operator()(int x, int y) {
	Color c;
	c.color =  &image[3*(y*w + x)];
	return c;
}

