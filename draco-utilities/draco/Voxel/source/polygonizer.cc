

#include "polygonizer.h"

using namespace std;
using namespace Vox;

template<typename T>
Polygonizer<T>::Polygonizer(byte isolevel): isolevel(isolevel) {}
template<typename T>
Polygonizer<T>::Polygonizer(float voxelSize, byte isolevel, Vector3<T> offset) :
    voxelSize(voxelSize), isolevel(isolevel), offset(offset) {}

template<typename T> void Polygonizer<T>::setTree(Tree* tree) {
	voxelSize = tree->voxSize;
	offset = tree->pos;
}