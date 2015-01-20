
#ifndef DRACO_SCALE_EXPORT_H
#define DRACO_SCALE_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_IMPORT_DRACO_SCALE
#		define DRACO_SCALE_API __declspec(dllimport)
#	else
#		define DRACO_SCALE_API __declspec(dllexport)
#	endif
#else
#	define DRACO_SCALE_API
#endif

#endif // DRACO_SCALE_EXPORT_H
