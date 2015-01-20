

#include "scaleManager.h"

#include <fstream>
#include <iostream>


const char *LINE_COMMENT_STRING = "#";


using namespace std;



///////////////////////
// utility functions //
///////////////////////

// trims a line from a file of comments
void prepareLine(string &line) {
	size_t comment = line.find_first_of(LINE_COMMENT_STRING);
	if (comment != string::npos)
		line.erase(comment, line.size() - comment);
}

// trims extraneous whitespace from a string
void trim(string &s) {
	s.erase(s.find_last_not_of(" \t\r\n") + 1);
	s.erase(0, s.find_first_not_of(" \t\r\n"));
}



///////////////////
// Scale Manager //
///////////////////

ScaleManager::ScaleManager(const std::string &scaleListPath): scaleListPath(scaleListPath) {
}
ScaleManager::~ScaleManager() {
}

void ScaleManager::loadScaleList(const std::string &scaleListPath) {
	this->scaleListPath = scaleListPath;
	loadScaleList();
}
void ScaleManager::loadScaleList() {
	ifstream listFile(scaleListPath.c_str());
	string line;

	while (!listFile.eof()) {
		getline(listFile, line);
		prepareLine(line);
		size_t equalsInd = line.find_first_of('=');
		if (equalsInd == string::npos)
			continue;

		string libPath = line.substr(0, equalsInd);
		string scaleName = line.substr(equalsInd +1);
		trim(libPath);
		trim(scaleName);

		if (scaleName.size() < 1 || libPath.size() < 1)
			continue;

		scales.push_back(ScaleType(scaleName, libPath));
		cout << "Added scale " << scaleName << " at " << libPath << endl;
	}
	listFile.close();
}

std::vector<ScaleType> &ScaleManager::getScales() {
	return scales;
}


