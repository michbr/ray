

#include "tree.h"

using namespace std;
using namespace Vox;

//////////////////
//  Tree class  //
//////////////////

Tree::Tree(byte maxDepth, double size): maxDepth(maxDepth), size(size), voxSize(size /(2 << maxDepth)), pos(0, 0, 0) {}



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
	return Index((byte)(depth +1), x *2, y *2, z *2);
}
Index Index::getChild(byte i) const {
	return Index((byte)(depth +1), x *2 +(i &4), y *2 +(i &2), z *2 +(i &1));
}
Index Index::getNeighbor(byte i) const {
	return Vox::Index(depth, x +(i &4), y +(i &2), z +(i &1));
}
Index Index::getParent(byte pDepth) const {
	byte diff = depth -pDepth;
	return Vox::Index(pDepth, x >> diff, y >> diff, z >> diff);
}
