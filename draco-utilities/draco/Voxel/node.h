
#ifndef DRACO_VOX_NODE_H
#define DRACO_VOX_NODE_H

#include "block.h"
#include "Voxel.h"


namespace Vox {

	class Node: public Block {
	public:
		// constants
		static const int CHILD_DIM = 2;
		static const int CHILD_COUNT = CHILD_DIM << 2;

		// ctor/dtor
		Node();
		Node(const Voxel& v);
		~Node();

		// getters
		byte getIndex(byte x, byte y, byte z) const;
//		Block get(byte x, byte y, byte z) const;
		Block* get(byte i) const;
		Node& getNode(byte i);

		// setters
		void set(byte i, Node* n);
		void set(byte i, const Voxel& v);
		// the following two do not free memory: IMPROPER USAGE COULD CAUSE MEMORY LEAKS
		void setNoClear(byte i, Node* n);
		void setNoClear(byte i, const Voxel& v);

		//
		bool compact() const;
		bool empty() const;
		byte average() const;

	protected:
		// members
		byte compactChildren;
		Node* children[CHILD_COUNT];

		bool compact(byte child) const;

	};

}


#endif // DRACO_VOX_NODE_H