
#ifndef DRACO_VOX_POLYONGIZER_H
#define DRACO_VOX_POLYONGIZER_H


#include "voxel.h"

#include <DragonMath/vector.h>
#include <unordered_map>
#include <vector>


namespace Vox {

    template<typename T>
	class Polygonizer {
	public:

		Polygonizer(float voxelSize, byte isolevel, Vector3<T> offset);

		virtual std::vector<int> lookupTriangles(int x, int y, int z, int x1, int y1, int z1, std::unordered_map<int, Vector3<T>>* vertices, Voxel*** voxels) const = 0;

		virtual Vector3<T> stretchVertex(int x1, int y1, int z1, int x2, int y2, int z2, Voxel valp1, Voxel valp2) const = 0;

	protected:
		float voxelSize;
		byte isolevel;
		Vector3<T> offset;

	};
}

#endif // DRACO_VOX_POLYONGIZER_H