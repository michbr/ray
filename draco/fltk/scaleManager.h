
//#pragma once
#ifndef DRACO_SCALE_MANAGER_H
#define DRACO_SCALE_MANAGER_H


#include "scaleType.h"

#include <vector>
#include <string>

//const char *SCALE_LIST_PATH = "config/scales.cfg";
#define SCALE_LIST_PATH "../config/scales.cfg"


class ScaleManager {
public:
	ScaleManager(const std::string &scaleListPath = SCALE_LIST_PATH);
	~ScaleManager();

	void loadScaleList();
	void loadScaleList(const std::string &scaleListPath);
	void constructScale(const std::string &scaleName) const;

	std::vector<ScaleType> &getScales();

private:
	std::string scaleListPath;
	std::vector<ScaleType> scales;

};

#endif // DRACO_SCALE_MANAER_H
