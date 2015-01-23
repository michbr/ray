
#pragma once

#include "scale.h"
#include "worldModel.h"
#include "FL/Fl_Group.H"

#include <string>


const char *TAB_NAME = "Ray Tracer";


class RayTracer: public Scale {
private:
	WorldModel* model;
	void loadModel(std::string pathi);
	static void handleButton(Fl_Widget* obj, void*);

public:
	RayTracer(ScaleType *type, Fl_Group *pane, const std::string &startDir);

	~RayTracer();



};

