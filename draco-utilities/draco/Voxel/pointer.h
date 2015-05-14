
#ifndef DRACO_VOXEL_POINTER_H
#define	DRACO_VOXEL_POINTER_H

#include "block.h"
#include "EXPORT.h"


namespace Vox {
	class DRACO_VOXEL_API Pointer {
	public:
		Block* block;
		byte child;
		
		Pointer();
		Pointer(Block* block, byte child);
		Pointer(const Pointer& source);
		
		Voxel get() const;
		Pointer traverse(byte child) const;
	};
}

#endif // DRACO_VOXEL_POINTER_H