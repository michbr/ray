
#ifndef DRACO_VOX_MARCHING_CUBES_H
#define DRACO_VOX_MARCHING_CUBES_H

#include "polygonizer.h"
#include "dragonmath.h"


class MarchingCubes: public Polygonizer {
public:

	MarchingCubes(float voxelSize,
		byte isolevel,
		ref Dictionary<int, object> vertices,
		ref Dictionary<int, byte> materials,
		ref Voxel[, ,] voxels,
		Vector3 offset,
		Vector3[] meshVerts);

private:
	static const unsigned short *edgeTable;
	static const byte *triTable;

};

#endif // DRACO_VOX_MARCHING_CUBES_H