
#ifndef DRACO_UTIL_EXPORT_H
#define DRACO_UTIL_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_EXPORT_DRACO_UTIL
#		define DRACO_UTIL_API __declspec(dllexport)
#	else
#		define DRACO_UTIL_API __declspec(dllimport)
#	endif
#else
#	define DRACO_UTIL_API
#endif

#endif // DRACO_UTIL_EXPORT_H
