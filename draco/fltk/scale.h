
#pragma once

class Scale;

#include "scale.WIN.h"
#include "scale.UNI.h"

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

