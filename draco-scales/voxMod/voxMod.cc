
#include "voxMod.h"
#include "common/directoryViewer.h"
#include "FL/Fl_Box.H"
#include "FL/Fl_File_Chooser.H"

#include <iostream>
#include <string>

using namespace std;


DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new VoxelModeler(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
	return VOXEL_MODELER_NAME;
}


VoxelModeler::VoxelModeler(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	display = new cube_box(this, 5, 30, 500, 500, 0);
	engine.initWindow(500, 500);
	engine.placeCamera (
		0, 0, 8.,
		0, 0, 0,
		0., 1., 0.
	);
	main = new Thread(this);
	main->start();
}
VoxelModeler::~VoxelModeler() {
	free(pane);
}

void VoxelModeler::run() {
	while(true) {
		this_thread::sleep_for(chrono::milliseconds(1000));
		Fl::awake((Fl_Awake_Handler)update, this);
	}
}

void VoxelModeler::initialize() {
	engine.initRenderer();
}

void VoxelModeler::draw() {
	engine.render();
}

void VoxelModeler::update(void * context) {
	VoxelModeler * instance = (VoxelModeler *) context;
	instance->display->redraw();
}

