#ifndef SCENE_OBJECT_OBJ_H
#define SCENE_OBJECT_OBJ_H

#include "vertex.h"
#include "material.h"
#include "face.h"

#include <vector>

class SceneObject {
private:
	std::vector<SceneObject * > children;
	std::vector<Material *> materials;
	std::vector<Vertex> vertices;
	std::unordered_map<int, Vertex *> textureVertices;
	std::vector<Face *> faces;
	std::vector<std::string> textures;	

		
public:
	SceneObject();
	void addChild(SceneObject * c);
	void addMaterial(Material * m);
	void addVertex(Vertex);
	void addVertex(Vertex, Vertex *);
	void addFace(Face * f);
	void addTexture(std::string path);

	const Material * getMaterial(int index);
	Vertex getVertex(int index);
	bool hasTexCoord(int index);
	Vertex * getTexVertex(int index);
	const std::vector<std::string> getTextures();
	std::vector<Face *> &getFaces();
	
};


#endif
