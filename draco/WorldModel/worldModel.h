#ifndef WORLD_MODEL_OBJ_H
#define WORLD_MODEL_OBJ_H

#include "texture.h"

#include "sceneObject.h"

#include "light.h"
#include "face.h"

#include <string>
#include <unordered_map>
#include <vector>

class WorldModel {
private:
	std::vector<SceneObject *> assets;
	std::vector<Texture *> textures;
//	std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };
//	bool getFiles(std::string dir, std::vector<std::string> & files);
public:
	WorldModel();
	void addObject(SceneObject *);//std::string filename);
	std::vector<Face *> & getFaces();
	std::vector<Light *> getLights();
};

#endif
