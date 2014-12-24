
#ifndef _WIN32

#pragma once

class Scale;

#include "scaleType.h"
#include "FL/Fl_Group.H"

#include <string>


#ifdef __cplusplus
extern "C" {
#endif

	Scale *constructScale(ScaleType *type, Fl_Group *pane, const std::string &file);

	const char *scaleName();

#ifdef __cplusplus
}
#endif

#endif // _WIN32