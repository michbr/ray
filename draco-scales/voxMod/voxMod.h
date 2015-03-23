
#ifndef DRACO_VOXEL_MODELER_H
#define DRACO_VOXEL_MODELER_H

#include "FL/Fl_Group.H"
#include "scale.h"
#include "Voxel/tree.h"
#include "Common/thread.h"

#include <string>
#include <vector>
#include <NewGLRenderer/dragon.h>
#include <common/glPane.h>


#ifdef __MINGW32__
	typedef _off64_t off64_t;
#endif

const char *VOXEL_MODELER_NAME = "Voxel Modeler";


class VoxelModeler: public Scale, public Runnable, public GLDrawable {
public:
	VoxelModeler(ScaleType *type, Fl_Group *pane, const std::string &startDir);
	~VoxelModeler();

	void draw();
	void initialize();
	void run();
	static void update(void * context);

private:
	std::vector<Vox::Tree> trees;
	DragonEngine engine;
	Thread * main;

	// GUI
	cube_box * display;

};


#endif // DRACO_VOXEL_MODELER_H