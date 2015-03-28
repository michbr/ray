#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "node.h"
#include "voxel.h"


namespace Vox {


    class Tree {
    public:
	    const byte maxDepth;
	    Node head;

	    Tree(byte maxDepth);

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
	};
}


#endif //DRACO_VOX_TREE_H
