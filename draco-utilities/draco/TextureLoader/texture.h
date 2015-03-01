#ifndef TEXTURE_OBJ_H
#define TEXTURE_OBJ_H

#include <vector>
//TODO fix this
#include "../../DevIL/include/IL/il.h"

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
