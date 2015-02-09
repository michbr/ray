#include "texture.h"

#include <iostream>

using namespace std;

Texture::Texture(int w, int h, ILubyte * data) {
	width = w;
	height = h;
	imageData = data;
	//cout << "Creating texture: " << width << "x" << height << endl;
}

void Texture::getPixel(int x, int y, std::vector<int> * out) {
			/*cout << "interior: " << x << ", " << y << endl;
			cout << "index: " << 4*(y*width + x) << endl;
			cout << "dims: " << width << ", " << height << endl;
			//out->push_back(1);
			cout << "val: " << static_cast<int>(imageData[0]) << endl;*/
			out->push_back(imageData[4*(y*width + x)]);
			out->push_back(imageData[4*(y*width + x) + 1]);
			out->push_back(imageData[4*(y*width + x) + 2]);
			/*cout << "color: "
				<< static_cast<int>(imageData[3*(y*width + x)]) << ", "
				<< static_cast<int>(imageData[3*(y*width + x) + 1]) << ", "
				<< static_cast<int>(imageData[3*(y*width + x) + 2]) << endl;*/
			//out->push_back(imageData[4*(y*width + x) + 3]);
		//	cout << width << ", " << height << endl;
		/*
		   	cout << static_cast<int>(imageData[4*(y*width + x)]) << ", "
			 << static_cast<int>(imageData[4*(y*width + x) + 1]) << ", "
			 << static_cast<int>(imageData[4*(y*width + x) + 2]) << ", "
			 << static_cast<int>(imageData[4*(y*width + x) + 3]) << endl;*/
}

int Texture::getWidth() {
return width;
}

int Texture::getHeight() {
return height;
}
