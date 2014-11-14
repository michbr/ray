#ifndef TEXTURE_OBJ_H
#define TEXTURE_OBJ_H

#include "IL/il.h"

#include <vector>

class TextureLoader;

class Texture {
friend class TextureLoader;
private:
	ILubyte * imageData;
	int width, height;
	Texture(int w, int, ILubyte * data);
public:
	void getPixel(int x, int y, std::vector<int> * out);
	int getWidth();
	int getHeight();
};

#endif
