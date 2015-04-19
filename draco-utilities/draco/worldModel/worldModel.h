#ifndef WORLD_MODEL_OBJ_H
#define WORLD_MODEL_OBJ_H

#include "cameraStructure.h"
#include "face.h"
#include "light.h"
#include "sceneObject.h"
#include "TextureLoader/texture.h"

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

class BaseRenderer;

class WorldModel {
public:
	WorldModel();
	WorldModel(const WorldModel &source);

	void addObject(SceneObject *);
	void removeObject(SceneObject *);
	std::vector<Face *> & getFaces();
	std::vector<Light *> getLights();

	std::vector<Vector3<double>> getVertices();
	std::vector<CameraStructure> cameras;

	void addRenderer(BaseRenderer &rend);
	void removeRenderer(BaseRenderer &rend);

private:
	std::unordered_set<SceneObject *> assets;
//	std::vector<Texture *> textures;
	std::list<BaseRenderer *> renderers;
//	std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };
//	bool getFiles(std::string dir, std::vector<std::string> & files);
};

#endif
