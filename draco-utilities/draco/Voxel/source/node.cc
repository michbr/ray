

#include "../node.h"
#include "voxel.h"

using namespace std;
using namespace Vox;


Node::Node(): compactChildren(0xFF) {}


byte Node::getIndex(byte x, byte y, byte z) const {
    return (byte)(x *(CHILD_DIM << 1) +y *CHILD_DIM +z);
}
Block Node::get(byte x, byte y, byte z) const {
	return get(getIndex(x, y, z));
}

Block Node::get(byte i) const {
	if (compactChildren & (1 << i)) {
		return Voxel::read(&children[i]);
	} else {
		return *children[i];
	}
}


void Node::set(byte i, Node* n) {
	if (compactChildren & (1 << i))
		delete children[i];
	setNoClear(i, n);
}
void Node::set(byte i, const Voxel& v) {
	if (compactChildren & (1 << i))
		delete children[i];
	setNoClear(i, v);
}

void Node::setNoClear(byte i, Node* n) {
	compactChildren = compactChildren & ~(1 << i);
	children[i] = n;
}
void Node::setNoClear(byte i, const Voxel &v) {
	compactChildren = compactChildren | (1 << i);
	Voxel::write(&children[i], v);
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