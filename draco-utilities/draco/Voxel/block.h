
#ifndef DRACO_VOX_BLOCK_H
#define DRACO_VOX_BLOCK_H


#include "voxel.h"


namespace Vox {

	class Block: public Voxel {
	public:
		
		Block();
		Block(const Voxel& source);
		Block(const Block& source);

	    virtual bool compact() const;
		virtual Voxel get(byte i) const;
		virtual const Block& getBlock(byte i) const;



	private:

	};

}


#endif // DRACO_VOX_BLOCK_H