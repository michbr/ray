#include "sceneObject.h"

#include <iostream>

using namespace std;

SceneObject::SceneObject() {

}

void SceneObject::addChild(SceneObject * c) {
	children.push_back(c);
}

void SceneObject::addVertex(Vector3<double> v) {
	vertices.push_back(v);
}

void SceneObject::addVertex(Vector3<double> vert, Vector3<double> * texVert) {
	int index = vertices.size();
	addVertex(vert);
	textureVertices[index] = texVert;
}

void SceneObject::addFace(Face * f) {
	faces.push_back(f);
	//cout << "adding face: " << faces.size() << endl;
}

void SceneObject::addMaterial(Material * m) {
	materials.push_back(m);
}

void SceneObject::addTexture(string texPath) {
	textures.push_back(texPath);
}

// TODO: KNOWN MEMORY LEAK!!!  In most cases, the faces are allocated in memory with no other references kept
void SceneObject::clearFaces() {
	faces.clear();
}

const Material * SceneObject::getMaterial(int index) {
	return materials[index];
}

Vector3<double> SceneObject::getVertex(int index) {
	return vertices[index];
}

Vector3<double> * SceneObject::getTexVertex(int index) {
	return textureVertices[index];
}

bool SceneObject::hasTexCoord(int index) {
	return textureVertices.count(index);
}

const vector<string> SceneObject::getTextures() {
	return textures;
}

vector<Face *> & SceneObject::getFaces() {
	/*cout << "got here" << endl;
	cout << faces.size() << endl;
	for (int i = 0; i < faces.size(); i++) {
		cout << i << endl;
	}*/
	return faces;
}
