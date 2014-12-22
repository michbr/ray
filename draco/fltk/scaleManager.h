
#pragma once

#include "scaleType.h"

#include <vector>
#include <string>

//const char *SCALE_LIST_PATH = "config/scales.cfg";


class ScaleManager {
public:
	ScaleManager(const std::string &scaleListPath = "config/scales.cfg");
	~ScaleManager();

	void loadScaleList();
	void loadScaleList(const std::string &scaleListPath);
	void loadScale(const std::string &libName);
	void constructScale(const std::string &scaleName) const;

private:
	std::string scaleListPath;
	std::vector<ScaleType> scales;

};

