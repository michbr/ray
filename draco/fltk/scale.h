
#pragma once

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

	Scale(ScaleType *type, Fl_Group *pane, const std::string &file);
	~Scale();

	const std::string &getLibName() const;
	const std::string &getFileName() const;
	const std::string &getName() const;

protected:

};


#ifdef __cplusplus
extern "C" {
#endif

Scale *constructScale(ScaleType *type, Fl_Group *pane, const std::string &file);

const char *scaleName();

#ifdef __cplusplus
}
#endif

