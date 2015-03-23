

#include "node.h"

using namespace std;
using namespace Vox;


Node::Node(): compactChildren(0xFF) {}

byte Node::getIndex(byte x, byte y, byte z) const {
    return (byte)(x *(CHILD_DIM << 1) +y *CHILD_DIM +z);
}

const Block &Node::get(byte i) const {
	if (compactChildren & (1 << i)) {
		return (Block &) children[i];
	} else {
		return *children[i];
	}
}
Block &Node::get(byte i) {
    if (compactChildren & (1 << i)) {
	    return (Block &) children[i];
    } else {
	    return *children[i];
    }
}
void Node::set(byte i, const Block &b) {
	if (b.compact()) {

	}
}

Block &Node::get(byte x, byte y, byte z) {
    return get(getIndex(x, y, z));
}
const Block &Node::get(byte x, byte y, byte z) const {
    return get(getIndex(x, y, z));
}


bool Node::compact() const {
    return sizeof(this) <= CHILD_COUNT;
}
bool Node::empty() const {
    for (int i = 0; i < CHILD_COUNT; ++i)
	    if (!get(i).empty())
		    return false;
    return true;
}
byte Node::average() const {
	int sum = 0;
	for(int i=0; i<CHILD_COUNT; ++i)
		sum += get(i).average();
	return (byte) (sum /CHILD_COUNT);
}