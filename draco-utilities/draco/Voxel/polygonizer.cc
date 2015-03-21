

#include "polygonizer.h"

using namespace std;


namespace Vox {

    template<typename T>
    Polygonizer::Polygonizer(float voxelSize, byte isolevel, Vector3<T> offset) :
	    voxelSize(voxelSize), isolevel(isolevel), offset(offset) {}

}