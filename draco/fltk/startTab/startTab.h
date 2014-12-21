
#pragma once

//#include "scale.h"

#include <string>


class StartTab {
public:

	static StartTab *load(const std::string &fileName);

	StartTab(const std::string &name, const std::string &fileName);
	~StartTab();

	const std::string &getFileName() const;
	const std::string &getName() const;

private:
	std::string fileName;
	std::string name;

};

