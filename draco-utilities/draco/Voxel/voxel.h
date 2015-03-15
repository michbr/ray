
#ifndef DRACO_VOX_ATOM_H
#define DRACO_VOX_ATOM_H


#include "block.h"

#include <iostream>


namespace Vox {

	class Block;

    typedef unsigned char byte;
    std::ostream &operator<<(std::ostream& out, byte value);

	class Voxel: Block {
	public:
		// members
		byte opacity;
		unsigned short material;

		// constructors
		Voxel(byte opacity, unsigned short material);
		Voxel(const Voxel& other);

		// methods
		bool compact() const;
		bool empty() const;
		byte average() const;

	private:

	};


}


#endif // DRACO_VOX_ATOM_H