
#include "pointer.h"

using namespace std;
using namespace Vox;


Pointer::Pointer(): block(NULL), child(0) {}
Pointer::Pointer(Block* block, byte child): block(block), child(child) {}
Pointer::Pointer(const Pointer& source): block(source.block), child(source.child) {}


Voxel Pointer::get() const {
	return block->get(child);
}
Pointer Pointer::traverse(byte child) const {
	if (block->compact(this->child))
		return *this;
	return Pointer(&block->getBlock(this->child), child);
}