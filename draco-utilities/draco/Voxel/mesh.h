#ifndef DRACO_VOX_MESH_H
#define DRACO_VOX_MESH_H

#include "voxel.h"
#include "meshIterator.h"
#include "tree.h"

#include <worldModel/sceneObject.h>


namespace Vox {

	class Tree;

    class Mesh {
    public:
	    static const byte VOXEL_DEPTH = 4;
	    static const byte VOXEL_DIMENSION = 1 << VOXEL_DEPTH;

		Mesh(Tree* tree);
		~Mesh();

		SceneObject* getObject();

		void update();

    private:
		Tree* tree;
		SceneObject object;

    };

}

#endif //DRACO_VOX_MESH_H
