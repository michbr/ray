
#ifndef DRACO_VOX_NODE_H
#define DRACO_VOX_NODE_H

#include "block.h"
#include "Voxel.h"


namespace Vox {

	class Node: public Block {
	public:
		static const int CHILD_DIM = 2;
		static const int CHILD_COUNT = CHILD_DIM << 2;

		Node();

		bool compact() const;
		bool empty() const;
		byte average() const;

		byte getIndex(byte x, byte y, byte z) const;
		Block get(byte x, byte y, byte z) const;
		Block get(byte i) const;

		void set(byte i, Node* n);
		void set(byte i, const Voxel& v);

		// the following two do not free memory: IMPROPER USAGE COULD CAUSE MEMORY LEAKS
		void setNoClear(byte i, Node* n);
		void setNoClear(byte i, const Voxel& v);


	protected:
		// members
		byte compactChildren;
		Node* children[CHILD_COUNT];

	};

}


#endif // DRACO_VOX_NODE_H