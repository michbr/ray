
#include "index.h"

using namespace std;
using namespace Vox;


///////////////////
//  Index class  //
///////////////////

// ctors
Index::Index(): Index(0) {}

Index::Index(byte depth): Index(depth, 0, 0, 0) {}

Index::Index(const Index& s): Index(s.depth, s.x, s.y, s.z) {}

Index::Index(byte depth, int x, int y, int z):
	depth(depth),
	x(x), y(y), z(z) {}

// methods
Index Index::getChild() const {
	return Index(depth +1, x *2, y *2, z *2);
}

Index Index::getChild(byte i) const {
	return Index(depth +1, x *2 +((i &4) >> 2), y *2 +((i &2) >> 1), z *2 +(i &1));
}

Index Index::getNeighbor(byte i) const {
	return Index(depth, x +((i &4) >> 2), y +((i &2) >> 1), z +(i &1));
}

Index Index::getParent(byte pDepth) const {
	byte diff = depth - pDepth;
	return Index(pDepth, x >> diff, y >> diff, z >> diff);
}

byte Index::directionTo(const Index& child) const {
    int halfWidth = 1 << (child.depth -depth);
    return (child.x -x *halfWidth) *4 | (child.y -y *halfWidth) *2 | (child.z -z *halfWidth);
}

bool Index::operator==(const Index& o) const {
	return x == o.x && y == o.y && z == o.z && depth == o.depth;
}
int &Index::operator[](int index) {
    return ((int *)this)[index];
}
int Index::operator[](int index) const {
    return ((int *)this)[index];
}




// hash
size_t hash<Index>::operator()(const Vox::Index& i) const {
	size_t h = i.x ^ i.y ^ i.z ^ i.depth;
	h = (h^0xdeadbeef) + (h<<4);
	h = h ^ (h>>10);
	h = h + (h<<7);
	return h ^ (h>>13);

	// different hash function, potentially worse
//	h = h ^ (h>>4);
//	h = (h^0xdeadbeef) + (h<<5);
//	return h ^ (h>>11);
}