
#pragma once

#include "image.h"
#include "imageWidget.h"
#include "renderer.h"
#include "scale.h"
#include "thread.h"
#include "worldModel.h"

#include "FL/Fl_Group.H"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <string>
#include <vector>

const char *TAB_NAME = "Ray Tracer";

class RayTracer: public Scale, public Runnable {
private:
	//widgets
	Fl_Output * selectedFileDisplay;
	Fl_Button * button;
	ImageBox * imageBox;	

	// utilities
	WorldModel* model;
	Renderer * renderer;
	Image * imageData;

	Thread * rayTracer;
	Thread * imageUpdater;
	Thread * displayUpdater;

	std::vector<Light *> * lights;
	void loadModel(std::string path);
	static void handleButton(Fl_Widget* obj, void*);

public:
	RayTracer(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	virtual void run();
	~RayTracer();
};

