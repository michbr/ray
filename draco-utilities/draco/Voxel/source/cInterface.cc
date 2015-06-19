
#include "cInterface.h"
#include "marchingCubes.h"
#include "mutators/sphere.h"
#include "tree.h"
#include "worldModel/renderer.h"

using namespace std;
using namespace Vox;



void* voxMakeTree(unsigned char maxDepth, double size) {
	Tree *t = new Tree(maxDepth, size);
	t->setPolygonizer(new MarchingCubes());
	t->addWorld(new WorldModel())
	return t;
}
void voxEraseTree(void* tree) {
	Tree* t = (Tree*) tree;
	delete t->getPolygonizer();
	delete t;
}

void voxSphereMutator(void* tree,
	double x, double y, double z,
	double radius, double opacity, unsigned short matType) {
	Tree* t = (Tree*)tree;
	SphereMut mut(Vector3<double>(x, y, z), radius, Voxel(((byte)opacity *((byte)-1)), matType));
	mut.apply(*t);
}


class WorldModelListener: public BaseRenderer {
public:
	virtual void addObject(SceneObject*) {
		
	}
	virtual void removeObject(SceneObject*) {
		
	}
	virtual void addCamera(CameraStructure* cam) {
		
	}
};

//int voxGetChangedMeshes(void* tree, int max, VoxIndex* indices, VoxMesh* meshes) {
//	Tree* t = (Tree*)tree;
//	SphereMut mut(Vector3<double>(x, y, z), radius, Voxel(((byte)opacity *((byte)-1)), matType));
//	mut.apply(*t);
//}
