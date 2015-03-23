
#ifndef DRACO_VOX_VOXEL_H
#define DRACO_VOX_VOXEL_H

#include <iostream>


namespace Vox {

    typedef unsigned char byte;
    std::ostream &operator<<(std::ostream& out, byte value);

	class Voxel {
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


#endif // DRACO_VOX_VOXEL_H