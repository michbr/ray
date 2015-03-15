
#ifndef DRACO_VOX_MARCHING_CUBES_H
#define DRACO_VOX_MARCHING_CUBES_H

#include "polygonizer.h"
#include "voxel.h"
#include "DragonMath/dragonmath.h"


namespace Vox {

	template<typename T>
	class MarchingCubes : public Polygonizer {
	public:

		MarchingCubes(float voxelSize,
			byte isolevel,
//			ref Dictionary<int, object> vertices,
//			ref Dictionary<int, byte> materials,
//			ref Voxel[, ,] voxels,
			Vector3<T> offset,
			Vector3<T> *meshVerts);



	private:
		static const unsigned short *edgeTable;
		static const byte *triTableLengths;
		static const byte **triTable;

	};
}

#endif // DRACO_VOX_MARCHING_CUBES_H