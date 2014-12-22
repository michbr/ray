
#pragma once

class Scale;

#include "scaleType.h"
#include "FL/Fl_Widget.H"

#include <string>



class Scale {
public:
	Scale(ScaleType *type);
	~Scale();

	const std::string &getFileName() const;
	const std::string &getName() const;

	virtual Fl_Widget *thingy() = 0;

private:
	ScaleType *type;

};



Scale *constructScale(ScaleType *type);

const char *scaleName();
