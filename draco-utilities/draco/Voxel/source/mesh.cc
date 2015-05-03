
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
	
//	cout << "populated" << endl;
	unordered_map<int, Vector3<double> > vertices;
	vector<vector<int> > rawTris;
	int totalTris = 0;
	Vector3<double> offset = tree->pos +Vector3<double>(iter.pos.x, iter.pos.y, iter.pos.z) *(double)VOXEL_DIMENSION *tree->voxSize;
	cout << iter.pos << endl;
	for(int x=1; x<VOXEL_DIMENSION; ++x) {
		for(int y=1; y<VOXEL_DIMENSION; ++y) {
			for(int z=1; z<VOXEL_DIMENSION; ++z) {
//				cout << "polygonizing" << endl;
				rawTris.push_back(tree->getPolygonizer()->lookupTriangles(x-1, y-1, z-1, x, y, z, &vertices, voxels, offset));
				totalTris += rawTris.back().size();
//				cout << " finished" << endl;
			}
		}
	}
	
//	cout << "polygonized" << endl;
//	unordered_map<int, int> vertexIndices;
//	vector<Vector3<double> > vertexList;
//	for(auto vertex: vertices) {
//		vertexIndices[vertex.first] = vertexList.size();
//		vertexList.push_back(vertex.second);
//	}
	
	// Working around "memory leak" with clearFaces method
	for(auto face: object.getFaces())
		delete face;
	object.clearFaces();
	
	for(auto tris: rawTris) {
		for(int i=0; i<tris.size(); i+=3) {
			Face* face = new Face(NULL);
			face->addVertex(vertices[tris[i]]);
			face->addVertex(vertices[tris[i+1]]);
			face->addVertex(vertices[tris[i+2]]);
//			cout << vertices[tris[i]] << "\n";
			object.addFace(face);
		}
	}
	
	cout << object.getFaces().size() << endl;
	for(auto world: tree->getWorlds()) {
		world->addObject(&object);
	}
	cout << "assigned" << endl;
}

void Mesh::populate(Pointer block, Index i, Voxel (*array)[VOXEL_DIMENSION][VOXEL_DIMENSION]) const {
	if (i.depth >= Mesh::VOXEL_DEPTH) {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			array[i.x +(c &4) /4][i.y +(c &2) /2][i.z +(c & 1)] = block.traverse(c).get();
//			if (block.traverse(c).get().opacity > 128)
//				cout << "yes!" << endl;
//			else
//				cout << "no!" << endl;
		}
	} else {
		for(byte c=0; c<Node::CHILD_COUNT; ++c) {
			block.traverse(c);
			populate(block.traverse(c), i.getChild(c), array);
		}
	}
}