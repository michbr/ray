
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H


#include "voxel.h"

#include <iostream>


namespace Vox {

	class Atom;

	typedef unsigned char byte;
	std::ostream &operator<<(std::ostream& out, byte value);

	class Block {
	public:

	    virtual bool compact() const = 0;
//		virtual byte depth() const = 0;
		virtual bool empty() const = 0;
		virtual byte average() const = 0;



	private:

	};

}


#endif // DRACO_VOX_VOXEL_H