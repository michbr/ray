
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H

//namespace Vox {
//    typedef unsigned char byte;
//}

#include "block.h"


namespace Vox {

	class Voxel: public Block {
	public:
		// members
		unsigned short material;
		byte opacity;

		// constructors
		Voxel(byte opacity, unsigned short material);
		Voxel(const Voxel& other);

		// methods
		bool compact() const;
		bool empty() const;
		byte average() const;

		static Voxel read(void *address);
		static void write(void *address, const Voxel&);

	private:

	};


}


#endif // DRACO_VOX_VOXEL_H