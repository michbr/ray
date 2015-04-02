#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "node.h"
#include "voxel.h"

#include <DragonMath/vector.h>


namespace Vox {


    class Tree {
    public:
	    const byte maxDepth;
	    const double size, voxSize;
	    Vector3<double> pos;
	    Node head;

	    Tree(byte maxDepth, double size);

    };


	class Index {
	public:
		byte depth;
		int x, y, z;

		Index();
		Index(byte depth);
		Index(byte depth, int x, int y, int z);
		Index(const Index& source);

		Index getChild() const;
		Index getChild(byte index) const;
		Index getNeighbor(byte index) const;
		Index getParent(byte depth) const;
	};
}


#endif //DRACO_VOX_TREE_H
