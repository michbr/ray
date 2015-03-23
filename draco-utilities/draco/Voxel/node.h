
#ifndef DRACO_VOX_NODE_H
#define DRACO_VOX_NODE_H

#include "block.h"

namespace Vox {

	class Node: Block {
	public:
		static const int CHILD_DIM = 2;
		static const int CHILD_COUNT = CHILD_DIM << 2;

		bool compact() const;
		bool empty() const;
		byte average() const;

		byte getIndex(byte x, byte y, byte z) const;


	protected:
		// members
		byte compactChildren;
		Block* children[CHILD_COUNT];

		Block & get(byte x, byte y, byte z);
		const Block & get(byte x, byte y, byte z) const;

		Block & get(byte i);
		const Block & get(byte i) const;

		void set(byte i, const Block &b);

	};

}


#endif // DRACO_VOX_NODE_H