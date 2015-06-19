
#ifndef DRACO_VOXEL_C_INTERFACE_H
#define DRACO_VOXEL_C_INTERFACE_H

#include "EXPORT.h"
#include "tree.h"
#include "mutators/sphere.h"


#ifdef __cplusplus
extern "C" {
#endif

	// note: automatically assigns a MarchingCubes polygonizer to the new tree
	DRACO_VOXEL_API Vox::Tree* voxMakeTree(unsigned char maxDepth, double size);
	typedef Vox::Tree*(* VoxMakeTreeFunc )(unsigned char maxDepth, double size);

	// note: automatically frees the polygonizer for the tree in addition to free all other memory associated with the tree
	DRACO_VOXEL_API void voxEraseTree(Vox::Tree* tree);
	typedef void(* VoxEraseTreeFunc )(Vox::Tree* tree);


	DRACO_VOXEL_API Vox::SphereMut* voxSphereMutator(Vox::Tree* tree,
		double x, double y, double z,
		double radius, double opacity, unsigned short matType);
	typedef Vox::SphereMut*(* VoxSphereMutatorFunc )(double x, double y, double z, double radis, double opacity, unsigned short matType);

#ifdef __cplusplus
}
#endif



#endif // DRACO_VOXEL_C_INTERFACE_H