#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include "sceneObject.h"

#include <string>

class AssetLoader {
private:
	AssetLoader();
public:
	static void loadAsset(std::string filename, SceneObject & out);
};

#endif
