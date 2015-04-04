#ifndef WORLD_MODEL_OBJ_H
#define WORLD_MODEL_OBJ_H

#include "TextureLoader/texture.h"
#include "sceneObject.h"
#include "light.h"
#include "face.h"
#include "renderer.h"

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>


class WorldModel {
public:
	WorldModel();
	WorldModel(const WorldModel &source);

	void addObject(SceneObject *);
	void removeObject(SceneObject *);
	std::vector<Face *> & getFaces();
	std::vector<Light *> getLights();

	std::vector<Vector3<double>> getVertices();

	void addRenderer(ModelRenderer &rend);
	void removeRenderer(ModelRenderer &rend);

private:
	std::unordered_set<SceneObject *> assets;
//	std::vector<Texture *> textures;
	std::list<ModelRenderer *> renderers;
//	std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };
//	bool getFiles(std::string dir, std::vector<std::string> & files);
};

#endif
