
#pragma once

#include "scale.h"
#include "worldModel.h"
#include "renderer.h"
#include "FL/Fl_Group.H"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

#include <string>
#include <thread>
#include <vector>

const char *TAB_NAME = "Ray Tracer";


class RayTracer: public Scale {
private:
	Fl_Output * selectedFileDisplay;
	Fl_Button * button;
	WorldModel* model;
	Renderer * renderer;
	std::vector<Light *> * lights;
	std::thread * runner;
	void loadModel(std::string pathi);
	static void handleButton(Fl_Widget* obj, void*);

public:
	RayTracer(ScaleType *type, Fl_Group *pane, const std::string &startDir);

	~RayTracer();



};

