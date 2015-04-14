
#include "block.h"

using namespace std;
using namespace Vox;


Block::Block(): Voxel(0, 0) {}
Block::Block(const Voxel& source): Voxel(source) {}
Block::Block(const Block& source): Voxel(source) {}

bool Block::compact() const {
    return sizeof(this) <= sizeof(void*);
}
Voxel Block::get(byte i) const {
	return *this;
}
const Block& Block::getBlock(byte i) const {
	return *this;
}