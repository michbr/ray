
#include "cInterface.h"
#include "marchingCubes.h"
#include "mutators/sphere.h"
#include "tree.h"

using namespace std;
using namespace Vox;



void* voxMakeTree(unsigned char maxDepth, double size) {
	Tree *t = new Tree(maxDepth, size);
	t->setPolygonizer(new MarchingCubes());
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
