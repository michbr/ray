
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

void Mesh::update(MeshIterator iter) {
	Voxel*** voxels;
	populate(*iter.blocks[1][1][1], Index(0), voxels);
}

void Mesh::populate(const Block& block, Index i, Voxel*** array) const {
	if (i.depth >= Mesh::VOXEL_DEPTH) {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			array[i.x +(c &4) /4][i.y +(c &2) /2][i.z +(c & 1)] = block.get(c);
		}
	} else {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			populate(block.getBlock(c), i.getChild(c), array);
		}
	}
}