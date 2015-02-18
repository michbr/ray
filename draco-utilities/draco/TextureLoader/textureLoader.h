#ifndef TEXTURE_LOADER_OBJ
#define TEXTURE_LOADER_OBJ

#include "texture.h"

#include <string>

class TextureLoader {
private:
	static bool initialized;
public:
	static Texture * loadTexture(std::string path);
};

#endif
