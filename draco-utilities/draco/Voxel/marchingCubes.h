
#ifndef DRACO_VOX_MARCHING_CUBES_H
#define DRACO_VOX_MARCHING_CUBES_H

#include "polygonizer.h"
#include "voxel.h"
#include "DragonMath/dragonmath.h"

#include <tr1/unordered_map>


namespace Vox {

	template<typename T>
	class MarchingCubes : public Polygonizer {
	private:
		static const unsigned short *edgeTable;
		static const byte *triTableLengths;
		static const byte **triTable;

	public:




		MarchingCubes(float voxelSize,
			byte isolevel,
//			ref Dictionary<int, object> vertices,
//			ref Dictionary<int, byte> materials,
//			ref Voxel[, ,] voxels,
			Vector3<T> offset,
			Vector3<T> *meshVerts);


		int *lookupTriangles(int x, int y, int z, int x1, int y1, int z1) const;

		Vector3<T> stretchVertex(int x1, int y1, int z1, int x2, int y2, int z2, Voxel valp1, Voxel valp2) const;



	private:
		std::tr1::unordered_map<int, Vector3<T>> vertices;
		std::tr1::unordered_map<int, byte> materials;
		float voxelSize;
		int *vertlist[12];
		byte isolevel;
		Voxel ***voxels;
		Vector3<T> offset;
		Vector3<T> *meshVerts;

	};
}

#endif // DRACO_VOX_MARCHING_CUBES_H