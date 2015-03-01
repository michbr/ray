//#include <il>
#include "textureLoader.h"


#include <iostream>
#include <cstdlib>

using namespace std;

bool TextureLoader::initialized = false;

Texture * TextureLoader::loadTexture(string path) {
	if (!initialized) {
		ilInit();
		initialized = true;
	}
	ILuint ImageName;
	
	ilGenImages(1, &ImageName);

	ilBindImage(ImageName);

	ilLoadImage(path.c_str());

	ILubyte *bytes = ilGetData();

	ILuint width, height;
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	//cout << "one" << hex << ilGetInteger(IL_IMAGE_FORMAT) << endl;
	//cout << "two" << hex << ilGetInteger(IL_IMAGE_TYPE) << endl;
	Texture * tex = new Texture(width, height, bytes);
//	tex->getPixel(0, 0, new vector<int>());
	return tex;

	
}

/*int main (int argc, char * argv [] ) {
	 if (argc != 2) {
                cerr << "Usage: " << argv[0] << " " << "<INPUT_IMAGE>" << endl;
                exit(1);
        }

	//vector<Texture> t;
	ILubyte * f;
	Texture * t = new Texture (0, 0 , f);
	//cout << "starting " << endl;
	TextureLoader::loadTexture(argv[1], t);
	//cout << "here?" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			vector<int> blah;
			t->getPixel(j, i, &blah);
			for (int c = 0; c < blah.size(); c++) {
				cout << blah[c] << ", ";
			}
			cout << endl;
		}
	}
	//t->getPixel(0, 0, new vector<int>());
	cout << "Done. " << endl;
}*/
