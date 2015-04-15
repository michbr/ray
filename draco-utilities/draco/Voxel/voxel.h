
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H

#include <iostream>


namespace Vox {

	typedef unsigned char byte;

	class Voxel {
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

std::ostream &operator<<(std::ostream& out, Vox::byte value);


#endif // DRACO_VOX_VOXEL_H