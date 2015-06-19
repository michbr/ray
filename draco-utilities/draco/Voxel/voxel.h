
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H

#include "EXPORT.h"
#include <iostream>


namespace Vox {

	typedef unsigned char byte;

	class DRACO_VOXEL_API Voxel {
	public:
		// members
		unsigned short material;
		byte opacity;

		// constructors
		Voxel();
		Voxel(byte opacity, unsigned short material);
		Voxel(const Voxel& other);

		static Voxel read(void *address);
		static void write(void *address, const Voxel&);

	private:

	};


}

DRACO_VOXEL_API std::ostream &operator<<(std::ostream& out, Vox::byte value);


#endif // DRACO_VOX_VOXEL_H