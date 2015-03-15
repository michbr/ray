
#ifndef DRACO_VOX_POLYONGIZER_H
#define DRACO_VOX_POLYONGIZER_H

#include "voxel.h"


namespace Vox {
	class Polygonizer {
	public:

		virtual int *lookupTriangles(int x, int y, int z, int x1, int y1, int z1) = 0;

		virtual void stretchVertex(int x1, int y1, int z1, int x2, int y2, int z2, Voxel valp1, Voxel valp2, int vox) = 0;

	private:

	};
}

#endif // DRACO_VOX_POLYONGIZER_H