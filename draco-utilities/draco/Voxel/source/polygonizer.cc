

#include "polygonizer.h"

using namespace std;
using namespace Vox;
	
//template class Polygonizer<double>;

//template<typename T>
Polygonizer::Polygonizer(byte isolevel): isolevel(isolevel) {}
//template<typename T>
Polygonizer::Polygonizer(double voxelSize, byte isolevel, Vector3<double> offset) :
    voxelSize(voxelSize), isolevel(isolevel), offset(offset) {}

void Polygonizer::setTree(Tree* tree) {
	voxelSize = tree->voxSize;
	offset = tree->pos;
}