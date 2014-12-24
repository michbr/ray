
#ifdef _WIN32

#pragma once

#include "scaleType.h"
#include "FL/Fl_Group.H"

#include <string>


class Scale;

#if defined DLL_IMPORT
	#define SCALE_API __declspec(dllimport)
#else
	#define SCALE_API __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const std::string &file);

	SCALE_API const char *scaleName();

#ifdef __cplusplus
}
#endif

#endif // _WIN32
