#ifndef DRACO_VOX_MESH_H
#define DRACO_VOX_MESH_H

#include "voxel.h"
#include "meshIterator.h"
#include "pointer.h"

#include <worldModel/sceneObject.h>


namespace Vox {

	class Tree;

    class Mesh {
    public:
	    static const byte VOXEL_DEPTH = 4;
	    static const byte VOXEL_DIMENSION = 1 << VOXEL_DEPTH;
		
		static unsigned long count;

		Mesh(Tree* tree);
		~Mesh();

		SceneObject* getObject();

		void update(MeshIterator iter);

    private:
		Tree* tree;
		SceneObject object;
		
		// depth must start at 0.
		void populate(Pointer block, Index i, Voxel array[][VOXEL_DIMENSION][VOXEL_DIMENSION]) const;

    };

}

#include "tree.h"

#endif //DRACO_VOX_MESH_H