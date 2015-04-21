
#include "block.h"

using namespace std;
using namespace Vox;


const Block Block::EMPTY = Block(Voxel(0, 0));

Block::Block(): Voxel(0, 0) {}
Block::Block(const Voxel& source): Voxel(source) {}
Block::Block(const Block& source): Voxel(source) {}
Block::~Block() {}

bool Block::compact(byte child) const {
	return false;
}
Voxel Block::get(byte i) const {
	return *this;
}
Block& Block::getBlock(byte i) {
	return *this;
}
const Block& Block::getBlock(byte i) const {
	return *this;
}