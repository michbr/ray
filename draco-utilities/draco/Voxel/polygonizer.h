
#ifndef DRACO_VOX_POLYONGIZER_H
#define DRACO_VOX_POLYONGIZER_H


#include "EXPORT.h"
#include "voxel.h"
#include "mesh.h"

#include <DragonMath/vector.h>
#include <unordered_map>
#include <vector>


namespace Vox {
	
	class Tree;

//    template<typename T>
	class DRACO_VOXEL_API Polygonizer {
	public:

		Polygonizer(byte isoLevel);
		Polygonizer(double voxelSize, byte isolevel);
		
		virtual void setTree(Tree* tree);

		virtual std::vector<int> lookupTriangles(int x, int y, int z, int x1, int y1, int z1, std::unordered_map<int, Vector3<double> >* vertices, Voxel voxels[][Mesh::VOXEL_DIMENSION][Mesh::VOXEL_DIMENSION], const Vector3<double>& offset) const = 0;

	protected:
		double voxelSize;
		byte isolevel;

	};
}

#endif // DRACO_VOX_POLYONGIZER_H