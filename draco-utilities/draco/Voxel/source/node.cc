
#include "node.h"

using namespace std;
using namespace Vox;


// ctors and dtor
Node::Node(): compactChildren(0xFF) {}

Node::Node(const Voxel &v) {
	for(byte i=0; i< CHILD_COUNT; ++i) {
		setNoClear(i, v);
	}
}

Node::~Node() {
	for(byte i=0; i< CHILD_COUNT; ++i) {
		if (!compact(i))
			delete children[i];
	}
}


// getters
byte Node::getIndex(byte x, byte y, byte z) const {
    return (byte)(x *(CHILD_DIM << 1) +y *CHILD_DIM +z);
}
//Block Node::get(byte x, byte y, byte z) const {
//	return get(getIndex(x, y, z));
//}

Block* Node::get(byte i) const {
	if (compact(i)) {
		return Voxel::read(&children[i]);
	} else {
		return children[i];
	}
}

Node& Node::getNode(byte i) {
	if (compact(i))
		set(i, new Node(Voxel::read(&children[i])));
	return *children[i];
}


// setters
void Node::set(byte i, Node* n) {
	if (!compact(i))
		delete children[i];
	setNoClear(i, n);
}
void Node::set(byte i, const Voxel& v) {
	if (!compact(i))
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
    return sizeof(Node) <= sizeof(void*);
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

bool Node::compact(byte child) const {
	return compactChildren & ((byte)1 << child);
}
