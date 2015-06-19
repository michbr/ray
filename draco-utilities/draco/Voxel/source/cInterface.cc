
#include "cInterface.h"
#include "marchingCubes.h"
#include "tree.h"
#include "worldModel/renderer.h"

using namespace std;
using namespace Vox;



Tree* voxMakeTree(unsigned char maxDepth, double size) {
	Tree *t = new Tree(maxDepth, size);
	t->setPolygonizer(new MarchingCubes());
	t->addWorld(new WorldModel());
	return t;
}

void voxEraseTree(Tree* tree) {
	Tree* t = (Tree*) tree;
	delete t->getPolygonizer();
	delete t;
}

SphereMut* voxSphereMutator(double x, double y, double z,
	double radius, double opacity, unsigned short matType) {
	return new SphereMut(Vector3<double>(x, y, z), radius, Voxel(((byte)opacity *((byte)-1)), matType));
}
