
#include "node.h"

#include <typeinfo>

using namespace std;
using namespace Vox;


// ctors and dtor
Node::Node(): compactChildren(0xFF) {}

Node::Node(const Voxel &v) {
	for(byte i=0; i< CHILD_COUNT; ++i) {
		setNoClear(i, v);
	}
}
Node::Node(const Node &n): Block(n) {
	for(byte i=0; i<CHILD_COUNT; ++i) {
		children[i] = n.children[i];
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

Voxel Node::get(byte i) const {
	return *((Voxel*) &children[i]);
}
const Block& Node::getBlock(byte i) const {
	return *children[i];
}
//Block Node::get(byte x, byte y, byte z) const {
//	return get(getIndex(x, y, z));
//}

//Voxel Node::get(byte i) const {
//	if (compact(i))
//		return (Voxel*) &children[i];
//	return children[i];
//}

Node& Node::getNode(byte i) {
	if (compact(i) || typeid(children[i]) != typeid(Node))
		set(i, new Node(Voxel::read(&children[i])));
	return *((Node*) children[i]);
}

byte Node::getOpacity() const {
    int sum = 0;
    for(byte i=0; i<CHILD_COUNT; ++i)
        sum += getOpacity(i);
    return (byte)(sum /CHILD_COUNT);
}
byte Node::getOpacity(byte i) const {
    if (compact(i))
		return ((Voxel*)&children[i])->opacity;
	return children[i]->opacity;
}

unsigned short Node::getMaterial() const {
    int mats[CHILD_COUNT+1];
    byte counts[CHILD_COUNT];
    mats[0] = -1;
    byte winner = 0;
    for(byte i=0; i<CHILD_COUNT; ++i) {
        unsigned int mat = getMaterial(i);
        byte j=0;
        for(;; ++j) {
            if (mats[j] < 0) {
                mats[j] = mat;
                mats[j+1] = -1;
                counts[j] = 1;
                break;
            } else if (mats[j] == mat) {
                ++counts[j];
                break;
            }
        }
        if (counts[winner] < counts[j])
            winner = j;
    }
    return winner;
}
unsigned short Node::getMaterial(byte i) const {
    if (compact(i))
		return ((Voxel*)&children[i])->material;
	return children[i]->material;
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
bool Node::compact(byte child) const {
	return compactChildren & ((byte)1 << child);
}
