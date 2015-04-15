
#ifndef DRACO_VOX_NODE_H
#define DRACO_VOX_NODE_H

#include "block.h"
#include "voxel.h"


namespace Vox {

	class Node: public Block {
	public:
		// constants
		static const int CHILD_DIM = 2;
		static const int CHILD_COUNT = CHILD_DIM << 2;

		// ctor/dtor
		Node();
		Node(const Voxel& v);
		Node(const Node& n);
		~Node();

		// getters
		byte getIndex(byte x, byte y, byte z) const;
		Node& getNode(byte i);
		byte getOpacity() const;
		byte getOpacity(byte i) const;
		unsigned short getMaterial() const;
		unsigned short getMaterial(byte i) const;

		// setters
		void set(byte i, Block* n);
		void set(byte i, const Voxel& v);
		// the following two do not free memory: IMPROPER USAGE COULD CAUSE MEMORY LEAKS
		void setNoClear(byte i, Block* n);
		void setNoClear(byte i, const Voxel& v);

		// override methods
		bool compact() const;
		Voxel get(byte i) const;
		const Block& getBlock(byte i) const;

	protected:
		// members
		byte compactChildren;
		Block* children[CHILD_COUNT];

		bool compact(byte child) const;

	};

}


#endif // DRACO_VOX_NODE_H