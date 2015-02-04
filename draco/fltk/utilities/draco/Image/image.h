#ifndef DRAGON_IMAGE_OBJECT
#define DRAGON_IMAGE_OBJECT

#include <cstddef>

/*class Color {
private:
	unsigned char color[3];
public:
	Color(unsigned char r, unsigned char g, unsigned char b);
	unsigned char r();
	unsigned char g();
	unsigned char b();
	
};*/

class Image {
private:
	class Color {
	private:
	        unsigned char* color;
	public:	
	        unsigned char r();
	        unsigned char g();
	        unsigned char b();
		void r(unsigned char);
		void g(unsigned char);
		void b(unsigned char);
		friend Image;
	};


	size_t w;
	size_t h;
	unsigned char* image;
public:
	Image(size_t width, size_t height);
	size_t getWidth();
	size_t getHeight();
	const unsigned char * getRawImage();

	const Color operator()(int x, int y) const;
	Color operator()(int x, int y);  
};

#endif
