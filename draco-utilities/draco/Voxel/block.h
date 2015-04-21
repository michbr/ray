
#ifndef DRACO_VOX_BLOCK_H
#define DRACO_VOX_BLOCK_H


#include "voxel.h"


namespace Vox {

	class Block: public Voxel {
	public:
		static const Block EMPTY;
		
		Block();
		Block(const Voxel& source);
		Block(const Block& source);
		virtual ~Block();

		virtual bool compact(byte child) const;
		virtual Voxel get(byte i) const;
		virtual Block& getBlock(byte i);
		virtual const Block& getBlock(byte i) const;



	private:

	};

}


#endif // DRACO_VOX_BLOCK_H