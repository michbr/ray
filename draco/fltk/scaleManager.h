
#pragma once

#include "scaleType.h"

#include <vector>
#include <string>


class ScaleManager {
public:
	ScaleManager();
	~ScaleManager();


	void loadScale(const std::string &libName);

	void constructScale(const std::string &scaleName);


private:
	std::vector<ScaleType> scales;

};

