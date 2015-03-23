
#ifndef DRACO_VOX_BLOCK_H
#define DRACO_VOX_BLOCK_H


#include "voxel.h"


namespace Vox {

	class Atom;

	class Block {
	public:

	    virtual bool compact() const = 0;
//		virtual byte depth() const = 0;
		virtual bool empty() const = 0;
		virtual byte average() const = 0;



	private:

	};

}


#endif // DRACO_VOX_BLOCK_H