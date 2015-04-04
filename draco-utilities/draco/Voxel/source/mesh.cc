
#include "mesh.h"

using namespace std;
using namespace Vox;


Mesh::Mesh(Tree *tree): tree(tree) {
	tree->pushMesh(&object);
}

Mesh::~Mesh() {
	tree->removeMesh(&object);
}


SceneObject* Vox::Mesh::getObject() {
	return &object;
}

void Mesh::update() {

}
