
//#pragma once
#ifndef DRACO_SCALE_H
#define DRACO_SCALE_H


class Scale;

#include "scaleType.h"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Group.H"

#include <string>



class Scale {
public:
	ScaleType *type;
	Fl_Group *pane;
	std::string file;

	Scale(ScaleType *type, Fl_Group *pane, const std::string &file): type(type), pane(pane), file(file) {}

	const std::string &getLibName() const;
	const std::string &getFileName() const;
	const std::string &getName() const;

protected:

};

#ifdef _WIN32
#	ifdef DLL_IMPORT_DRACO_SCALE
#		define DRACO_SCALE_API __declspec(dllimport)
#	else
#		define DRACO_SCALE_API __declspec(dllexport)
#	endif
#else
#	define DRACO_SCALE_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

	DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const std::string &file);

	DRACO_SCALE_API const char *scaleName();

#ifdef __cplusplus
}
#endif


#endif // DRACO_SCALE_H
