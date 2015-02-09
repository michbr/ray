
#ifndef DRACO_COMMON_EXPORT_H
#define DRACO_COMMON_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_EXPORT_DRACO_COMMON
#		define DRACO_COMMON_API __declspec(dllexport)
#	else
#		define DRACO_COMMON_API __declspec(dllimport)
#	endif
#else
#	define DRACO_COMMON_API
#endif

#endif // DRACO_COMMON_EXPORT_H
