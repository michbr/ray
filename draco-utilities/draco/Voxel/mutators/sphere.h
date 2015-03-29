
#ifndef DRACO_VOXEL_SPHERE_MODIFIER_H
#define DRACO_VOXEL_SPHERE_MODIFIER_H

#include "mutator.h"

#include <DragonMath/vector.h>


namespace Vox {
    class SphereMut: Mutator {
    public:
	    SphereMut(const Vector3);

	    Voxel mutate(const Index& pos, Block) const;
	    Mutator::TAction action(const Index& pos) const;
    };
}


#endif // DRACO_VOXEL_SPHERE_MODIFIER_H