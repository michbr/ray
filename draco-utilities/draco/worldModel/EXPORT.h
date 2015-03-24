
#ifndef DRACO_WORLD_MODEL_EXPORT_H
#define DRACO_WORLD_MODEL_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_EXPORT_DRACO_WORLD_MODEL
#		define DRACO_WORLD_MODEL_API __declspec(dllexport)
#	else
#		define DRACO_WORLD_MODEL_API __declspec(dllimport)
#	endif
#else
#	define DRACO_WORLD_MODEL_API
#endif

#endif // DRACO_WORLD_MODEL_EXPORT_H