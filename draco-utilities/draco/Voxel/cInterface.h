
#ifndef DRACO_VOXEL_C_INTERFACE_H
#define DRACO_VOXEL_C_INTERFACE_H

#include "EXPORT.h"
#include "tree.h"



struct VoxVertex {
	float x, y, z;
};

struct VoxMesh {
	VoxVertex* vertices;
	unsigned short* triangles;
};

struct VoxIndex {
	int x, y, z;
	unsigned char depth;
};


// note: automatically assigns a MarchingCubes polygonizer to the new tree
DRACO_VOXEL_API void* voxMakeTree(unsigned char maxDepth, double size);
typedef void*(*VoxMakeTreeFunc)(unsigned char maxDepth, double size);

// note: automatically frees the polygonizer for the tree in addition to free all other memory associated with the tree
DRACO_VOXEL_API void voxEraseTree(void* tree);
typedef void(*VoxEraseTreeFunc)(void* tree);


DRACO_VOXEL_API void voxSphereMutator(void* tree,
	double x, double y, double z,
	double radius, double opacity, unsigned short matType);
typedef void(*VoxSphereMutatorFunc)(void* tree, double x, double y, double z, double radis, double opacity, unsigned short matType);

//DRACO_VOXEL_API int voxGetChangedMeshes(void* tree, int max, VoxIndex* indices, VoxMesh* meshes);



#endif // DRACO_VOXEL_C_INTERFACE_H