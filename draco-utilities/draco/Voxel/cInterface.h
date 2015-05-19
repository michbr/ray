
#ifndef DRACO_VOXEL_C_INTERFACE_H
#define DRACO_VOXEL_C_INTERFACE_H

#include "EXPORT.h"


// note: automatically assigns a MarchingCubes polygonizer to the new tree
DRACO_VOXEL_API void* voxMakeTree(unsigned char maxDepth, double size);

// note: automatically frees the polygonizer for the tree
DRACO_VOXEL_API void voxEraseTree(void* tree);


DRACO_VOXEL_API void voxSphereMutator(void* tree,
	double x, double y, double z,
	double radius, double opacity, unsigned short matType);





#endif // DRACO_VOXEL_C_INTERFACE_H