
#ifndef DRACO_VOXEL_MODELER_H
#define DRACO_VOXEL_MODELER_H

#include <NewGLRenderer/dragon.h>
#include <common/glPane.h>
#include <common/thread.h>
#include <FL/Fl_Group.H>
#include <scale.h>
#include <string>
#include <vector>
#include <Voxel/tree.h>


// this works around a bug in MinGW
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
	std::vector<Vox::Tree*> trees;
	Vox::Polygonizer<double>* polygonizer;
	DragonEngine engine;
	Thread * main;
    WorldModel* world;

	// GUI
	cube_box * display;
	

	void addTree(byte depth, double width);
};


#endif // DRACO_VOXEL_MODELER_H