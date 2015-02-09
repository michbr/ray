#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include "worldModel.h"

#include <string>

class AssetLoader {
private:
	AssetLoader();
public:
	static void loadAsset(std::string filename, WorldModel & out);
};

#endif
