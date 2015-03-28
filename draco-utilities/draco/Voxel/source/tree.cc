

#include "../tree.h"

using namespace std;
using namespace Vox;

//////////////////
//  Tree class  //
//////////////////

Tree::Tree() {}



///////////////////
//  Index class  //
///////////////////

Index::Index(): Index(0) {}
Index::Index(byte depth,): Index(depth, 0, 0, 0) {}
Index::Index(const Index& s): Index(s.depth, s.x, s.y, s.z) {}

Index::Index(byte depth, int x, int y, int z):
	depth(depth),
	x(x), y(y), z(z) {}
