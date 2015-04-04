
#include "index.h"

using namespace std;
using namespace Vox;


///////////////////
//  Index class  //
///////////////////

// ctors
Index::Index(): Index(0) {}

Index::Index(unsigned char depth): Index(depth, 0, 0, 0) {}

Index::Index(const Index& s): Index(s.depth, s.x, s.y, s.z) {}

Index::Index(unsigned char depth, int x, int y, int z):
	depth(depth),
	x(x), y(y), z(z) {}

// methods
Index Index::getChild() const {
	return Index((unsigned char)(depth +1), x *2, y *2, z *2);
}

Index Index::getChild(unsigned char i) const {
	return Index((unsigned char)(depth +1), x *2 +(i &4), y *2 +(i &2), z *2 +(i &1));
}

Index Index::getNeighbor(unsigned char i) const {
	return Index(depth, x +(i &4), y +(i &2), z +(i &1));
}

Index Index::getParent(unsigned char pDepth) const {
	unsigned char diff = depth - pDepth;
	return Index(pDepth, x >> diff, y >> diff, z >> diff);
}

bool Index::operator==(const Index& o) const {
	return x == o.x && y == o.y && z == o.z && depth == o.depth;
}




// hash
size_t hash<Index>::operator()(const ::Vox::Index& i) const {
	size_t h = i.x ^ i.y ^ i.z;
	h = (h^0xdeadbeef) + (h<<4);
	h = h ^ (h>>10);
	h = h + (h<<7);
	return h ^ (h>>13);

	// different hash function, potentially worse
//	h = h ^ (h>>4);
//	h = (h^0xdeadbeef) + (h<<5);
//	return h ^ (h>>11);
}