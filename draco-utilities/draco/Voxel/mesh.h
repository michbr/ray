#ifndef DRACO_VOX_MESH_H
#define DRACO_VOX_MESH_H

#include "voxel.h"
#include "meshIterator.h"

#include <worldModel/sceneObject.h>


namespace Vox {

    class Mesh {
    public:
	    static const byte VOXEL_DEPTH = 4;
	    static const byte VOXEL_DIMENSION = 1 << VOXEL_DEPTH;

		void update();

    private:
		SceneObject *object;

    };

}

#endif //DRACO_VOX_MESH_H
