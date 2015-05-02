
#ifndef DRACO_VOX_MARCHING_CUBES_H
#define DRACO_VOX_MARCHING_CUBES_H

#include "DragonMath/dragonmath.h"
#include "mesh.h"
#include "polygonizer.h"
#include "voxel.h"

#include <unordered_map>
#include <vector>


namespace Vox {

	template<typename T>
	class MarchingCubes: public Polygonizer<T> {
	public:
		static const byte VERTEX_DIMENSION = Mesh::VOXEL_DIMENSION + 2;

		MarchingCubes(byte isolevel);
		MarchingCubes(float voxelSize, byte isolevel, Vector3<T> offset);

		std::vector<int> lookupTriangles(int x, int y, int z, int x1, int y1, int z1, std::unordered_map<int, Vector3<T> >* vertices, Voxel voxels[][Mesh::VOXEL_DIMENSION][Mesh::VOXEL_DIMENSION]) const;
		Vector3<T> stretchVertex(int x1, int y1, int z1, int x2, int y2, int z2, Voxel valp1, Voxel valp2) const;

		int getX(int x, int y, int z) const;
		int getY(int x, int y, int z) const;
		int getZ(int x, int y, int z) const;

	};
}

#endif // DRACO_VOX_MARCHING_CUBES_H