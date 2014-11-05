#include "sceneObject.h"

#include <iostream>

using namespace std;

SceneObject::SceneObject() {

}

void SceneObject::addChild(SceneObject * c) {
	children.push_back(c);
}

void SceneObject::addVertex(Vertex v) {
	vertices.push_back(v);
}

void SceneObject::addVertex(Vertex vert, Vertex * texVert) {
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

const Material * SceneObject::getMaterial(int index) {
	return materials[index];
}

Vertex SceneObject::getVertex(int index) {
	return vertices[index];
}

Vertex * SceneObject::getTexVertex(int index) {
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
