
#ifndef DRACO_VOXEL_SPHERE_MODIFIER_H
#define DRACO_VOXEL_SPHERE_MODIFIER_H

#include "../EXPORT.h"
#include "../mutator.h"

#include <DragonMath/vector.h>


namespace Vox {
    class DRACO_VOXEL_API SphereMut: public Mutator {
    public:
	    SphereMut(const Vector3<double>& pos, double radius, const Voxel& value);

	    Action mutate(Application* app, const Index& pos, byte index, Node& parent) const;
	    Application* setup(Tree& target) const;
//	    Mutator::TAction action(const Index& pos) const;

    protected:
	    Voxel value;
	    Vector3<double> pos;
	    double radius;
		
		class SphereApplication: public Application {
		public:
			double minRadius, minRadSqr, maxRadius, maxRadSqr;
		};
    };
}


#endif // DRACO_VOXEL_SPHERE_MODIFIER_H