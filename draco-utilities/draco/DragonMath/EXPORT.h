
#ifndef DRACO_DRAGON_MATH_EXPORT_H
#define DRACO_DRAGON_MATH_EXPORT_H

#ifdef _WIN32
#	ifdef DLL_EXPORT_DRACO_DRAGON_MATH
#		define DRACO_DRAGON_MATH_API __declspec(dllexport)
#		define DRACO_DRAGON_MATH_EXTERN
#	else
#		define DRACO_DRAGON_MATH_API __declspec(dllimport)
#		define DRACO_DRAGON_MATH_EXTERN extern
#	endif
#else
#	define DRACO_DRAGON_MATH_API
#	define DRACO_DRAGON_MATH_EXTERN
#endif

#endif // DRACO_DRAGON_MATH_EXPORT_H
