
#pragma once

#include <string>


class Scale {
public:

	static Scale *load(const std::string &fileName);

	Scale(const std::string &name, const std::string &fileName);
	~Scale();

	const std::string &getFileName() const;
	const std::string &getName() const;

private:
	std::string fileName;
	std::string name;

};

