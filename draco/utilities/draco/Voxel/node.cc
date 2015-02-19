

#include "node.h"


namespace Vox {
    byte Node::getIndex(byte x, byte y, byte z) const {
	    return (byte)(x * 4 + y * 2 + z);
    }

    Block &Node::get(byte i) {
	    if (compactChildren & (1 << i)) {
		    return (Block &) children[i];
	    } else {
		    return *children[i];
	    }
    }
    const Block &Node::get(byte i) const {
	    if (compactChildren & (1 << i)) {
		    return (Block &) children[i];
	    } else {
		    return *children[i];
	    }
    }
	void Node::set(byte i, const Block &b) {
		if (b.compact()) {
			chi
		}
	}

    Block &Node::get(byte x, byte y, byte z) {
	    return get(getIndex(x, y, z));
    }
    const Block &Node::get(byte x, byte y, byte z) const {
	    return get(getIndex(x, y, z));
    }


    bool Node::compact() const {
	    return sizeof(this) <= 8;
    }
    bool Node::empty() const {
	    for (int i = 0; i < 8; ++i)
		    if (!get(i).empty())
			    return false;
	    return true;
    }
	byte Node::average() const {
		int sum = 0;
		for(int i=0; i<8; ++i)
			sum += get(i).average();
		return (byte) (sum /8);
	}
}