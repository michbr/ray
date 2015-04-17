
#ifndef DRACO_VOXEL_SPHERE_MODIFIER_H
#define DRACO_VOXEL_SPHERE_MODIFIER_H

#include "../mutator.h"

#include <DragonMath/vector.h>


namespace Vox {
    class SphereMut: public Mutator {
    public:
	    SphereMut(const Vector3<double>& pos, double radius, const Voxel& value);

	    bool mutate(const Tree& target, const Index& pos, byte index, Node& parent, void* cache) const;
	    void getBounds(const Tree& target, Index& min, Index& max, void* cache) const;
//	    Mutator::TAction action(const Index& pos) const;

    protected:
	    Voxel value;
	    Vector3<double> pos;
	    double radius;
		double minRadius, minRadSqr, maxRadius, maxRadSqr;
    };
}


#endif // DRACO_VOXEL_SPHERE_MODIFIER_H