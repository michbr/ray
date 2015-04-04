#ifndef SCENE_OBJECT_OBJ_H
#define SCENE_OBJECT_OBJ_H

#include "material.h"
#include "face.h"

#include <vector>

class SceneObject {
private:
	std::vector<SceneObject * > children;
	std::vector<Material *> materials;
	std::vector<Vector3<double>> vertices;
	std::unordered_map<int, Vector3<double> *> textureVertices;
	std::vector<Face *> faces;
	std::vector<std::string> textures;	

		
public:
	SceneObject();
	void addChild(SceneObject * c);
	void addMaterial(Material * m);
	void addVertex(Vector3<double>);
	void addVertex(Vector3<double>, Vector3<double> *);
	void addFace(Face * f);
	void addTexture(std::string path);
	void clearFaces();

	const Material * getMaterial(int index);
	Vector3<double> getVertex(int index);
	bool hasTexCoord(int index);
	Vector3<double> * getTexVertex(int index);
	const std::vector<std::string> getTextures();
	std::vector<Face *> &getFaces();
	
};


#endif
