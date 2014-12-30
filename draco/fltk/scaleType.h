
//#pragma once
#ifndef DRACO_SCALE_TYPE_H
#define DRACO_SCALE_TYPE_H


#define NAME_GETTER_NAME "scaleName"
#define CONSTRUCTOR_NAME "constructScale"
class ScaleType;

#include "scale.h"
#include "FL/Fl_Group.H"

#include <string>


typedef Scale *(*ScaleConstructor)(ScaleType *type, Fl_Group *pane, const std::string &file);
typedef const char *(*ScaleNameGetter)();


class ScaleType {
public:
	std::string name;
	ScaleType(const std::string &name, const std::string &libName);
	~ScaleType();

	void load();
	void unload();
	bool loaded();
	void *loadFunction(const std::string &funcName) const;

	const std::string &getLibName() const;
	const char *getLibExtension() const;
	const char *getRealName() const;

	Scale *construct(Fl_Group *pane, const std::string &file);

private:
	std::string libName;

	void *lib;
	ScaleConstructor scaleConstructor;
	ScaleNameGetter nameGetter;

	void *loadLibrary();
};


#endif // DRACO_SCALE_TYPE_H
