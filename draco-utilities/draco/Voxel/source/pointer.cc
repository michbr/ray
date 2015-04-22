
#include "pointer.h"

using namespace std;
using namespace Vox;


Pointer::Pointer(): block(NULL), child(0) {
	if (child > 7) cout << "NO!" << endl;
}
Pointer::Pointer(Block* block, byte child): block(block), child(child) {
	if (child > 7) cout << "NO!" << endl;
}
Pointer::Pointer(const Pointer& source): block(source.block), child(source.child) {
	if (child > 7) cout << "NO!" << endl;
}


Voxel Pointer::get() const {
	return block->get(child);
}
Pointer Pointer::traverse(byte child) const {
	// TODO: remove this check
	if (child > 7) {cout << "NO!" << endl; return *this;}
	if (block->compact(this->child))
		return *this;
	return Pointer(&block->getBlock(this->child), child);
}