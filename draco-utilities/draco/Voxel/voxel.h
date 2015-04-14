
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H

#include <iostream>


namespace Vox {

    typedef unsigned char byte;
    std::ostream &operator<<(std::ostream& out, byte value);

	class Voxel {
	public:
		// members
		unsigned short material;
		byte opacity;

		// constructors
		Voxel(byte opacity, unsigned short material);
		Voxel(const Voxel& other);

		static Voxel read(void *address);
		static void write(void *address, const Voxel&);

	private:

	};


}


#endif // DRACO_VOX_VOXEL_H