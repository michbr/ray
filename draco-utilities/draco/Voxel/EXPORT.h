
#ifndef DRACO_VOXEL_EXPORT_H
#define DRACO_VOXEL_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_EXPORT_DRACO_VOXEL
#		define DRACO_VOXEL_API __declspec(dllexport)
#	else
#		define DRACO_VOXEL_API __declspec(dllimport)
#	endif
#else
#	define DRACO_VOXEL_API
#endif

#endif // DRACO_WORLD_MODEL_EXPORT_H