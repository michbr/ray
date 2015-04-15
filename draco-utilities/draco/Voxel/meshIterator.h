
#ifndef DRACO_VOXEL_MESH_ITERATOR_H
#define DRACO_VOXEL_MESH_ITERATOR_H

#include "index.h"
#include "node.h"
#include "pointer.h"


namespace Vox {
	class Tree;
	
	class MeshIterator {
	public:
        static const byte DIMMENSION = 3;
		Index pos;
        Pointer blocks[DIMMENSION][DIMMENSION][DIMMENSION];
        Tree* tree;
        
        MeshIterator(Tree* tree, const Index& startPos);
        
        void traverse(byte i);


	};
}


#endif // DRACO_VOXEL_MESH_ITERATOR_H