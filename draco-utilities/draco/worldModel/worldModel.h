#ifndef WORLD_MODEL_OBJ_H
#define WORLD_MODEL_OBJ_H

#include "cameraStructure.h"
#include "face.h"
#include "EXPORT.h"
#include "light.h"
#include "sceneObject.h"

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

class BaseRenderer;

class DRACO_WORLD_MODEL_API WorldModel {
public:
	WorldModel();
	WorldModel(const WorldModel &source);

	virtual void addObject(SceneObject *);
	virtual void removeObject(SceneObject *);
	virtual std::vector<Face *> & getFaces();
	std::vector<Light *> getLights();

	virtual std::vector<Vector3<double>> getVertices();

	virtual void addRenderer(BaseRenderer &rend);
	virtual void removeRenderer(BaseRenderer &rend);

private:
	std::unordered_set<SceneObject *> assets;
//	std::vector<Texture *> textures;
	std::list<BaseRenderer *> renderers;
	std::vector<CameraStructure> cameras;
//	std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };
//	bool getFiles(std::string dir, std::vector<std::string> & files);
};

#endif
