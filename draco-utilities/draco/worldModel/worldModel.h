#ifndef WORLD_MODEL_OBJ_H
#define WORLD_MODEL_OBJ_H

#include "TextureLoader/texture.h"
#include "sceneObject.h"
#include "light.h"
#include "face.h"
#include "renderer.h"

#include <string>
#include <unordered_map>
#include <vector>


class WorldModel {
public:
	WorldModel();
	WorldModel(const WorldModel &source);

	void addObject(SceneObject *);
	std::vector<Face *> & getFaces();
	std::vector<Light *> getLights();

	std::vector<Vector3<double>> getVertices();

	void assignRenderer(Renderer &rend);

private:
	std::vector<SceneObject *> assets;
	std::vector<Texture *> textures;
	Renderer *renderer;
//	std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };
//	bool getFiles(std::string dir, std::vector<std::string> & files);
};

#endif
