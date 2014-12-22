
#pragma once

class Scale;

#include "scaleType.h"

#include <string>



class Scale {
public:
	Scale(ScaleType *type);
	~Scale();

	const std::string &getFileName() const;
	const std::string &getName() const;

private:
	ScaleType *type;

};



Scale *constructScale(ScaleType *type);

const char *scaleName();
