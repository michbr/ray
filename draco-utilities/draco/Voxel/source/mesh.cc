
#include <vector>

#include "mesh.h"

using namespace std;
using namespace Vox;


unsigned long Mesh::count = 0;

Mesh::Mesh(Tree *tree): tree(tree) {
	++count;
	tree->pushMesh(&object);
}

Mesh::~Mesh() {
	--count;
	tree->removeMesh(&object);
}


SceneObject* Vox::Mesh::getObject() {
	return &object;
}

void Mesh::update(MeshIterator iter) {
	Voxel voxels[VOXEL_DIMENSION][VOXEL_DIMENSION][VOXEL_DIMENSION];
	populate(iter.blocks[1][1][1], Index(1), voxels);
	
//	unordered_map<int, Vector3<double> > vertices;
//	vector<vector<int> > rawTris;
//	for(int x=1; x<VOXEL_DIMENSION; ++x) {
//		for(int y=1; y<VOXEL_DIMENSION; ++y) {
//			for(int z=1; z<VOXEL_DIMENSION; ++z) {
//				rawTris.push_back(tree->getPolygonizer()->lookupTriangles(x-1, y-1, z-1, x, y, z, &vertices, voxels));
//			}
//		}
//	}
//	
//	unordered_map<int, int> vertexIndices;
//	vector<Vector3<double> > vertexList;
//	for(auto vertex: vertices) {
//		vertexList.push_back(vertex.second);
////		vertexIndices[]
//	}
	
}

void Mesh::populate(Pointer block, Index i, Voxel (*array)[VOXEL_DIMENSION][VOXEL_DIMENSION]) const {
	if (i.depth >= Mesh::VOXEL_DEPTH) {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			array[i.x +(c &4) /4][i.y +(c &2) /2][i.z +(c & 1)] = block.traverse(c).get();
		}
	} else {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			block.traverse(c);
			populate(block.traverse(c), i.getChild(c), array);
		}
	}
}