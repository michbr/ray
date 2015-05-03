
#include "voxMod.h"

#include <common/directoryViewer.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>
#include <string>
#include <Voxel/marchingCubes.h>
#include <Voxel/mutators/sphere.h>
#include <Voxel/tree.h>
#include <Voxel/voxel.h>

using namespace std;
using namespace Vox;


DRACO_SCALE_API Scale* constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new VoxelModeler(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
	return VOXEL_MODELER_NAME;
}


void VoxelModeler::addTree(byte depth, double width) {
    Tree* t = new Tree(depth, width);
	t->pos = Vector3<double>(-3, -3, 0);
    trees.push_back(t);
    t->addWorld(world);
    t->setPolygonizer(polygonizer);
    SphereMut mut(Vector3<double>(width, width, width) /2, width /3, Vox::Voxel(255, 1));
    mut.apply(*t);
	for(int i=0; i<8; ++i)
		t->head.set(i, Vox::Voxel(255, 1));
//	t->head.set(0, Vox::Voxel(255, 1));
//	t->head.set(5, Vox::Voxel(255, 1));
    t->updateMeshes();
	cout << "Nodes: " << Vox::Node::count << endl;
	cout << "Meshes: " << Vox::Mesh::count << endl;
	cout << "Vox size: " << t->voxSize << endl;
	cout << "Voxel size (bytes): " << sizeof(Vox::Voxel) << endl;
}

VoxelModeler::VoxelModeler(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir), world(new WorldModel) {
	pane->current(pane);
	display = new GLPane(this, 5, 30, 500, 500, 0);
	renderer.addCamera(new CameraStructure(
		Vector3<double>(0, 0, 8.),
		Vector3<double>(0, 1, 0),
		Vector3<double>(0, 0, 1))
	);
	
//	Vox::Index test1(0, 0, 0, 0);
//	Vox::Index test2(2, 3, 0, 0);
//	Vox::byte direction = test1.directionTo(test2);
//	cout << test1.getChild(direction) << " " << direction << endl;
//	for(Index i(test1); i.depth<=test2.depth; i.getChild())
//	cout << test1.getChild(test1.getChild(test1.directionTo(test2)).directionTo(test2)) << endl;
	
	main = new Thread(this);
	main->start();
}
VoxelModeler::~VoxelModeler() {
	free(pane);
    for(auto tree: trees)
        delete tree;
    delete world;
}

void VoxelModeler::run() {
	while(true) {
		this_thread::sleep_for(chrono::milliseconds(1000));
		Fl::awake((Fl_Awake_Handler)update, this);
	}
}

void VoxelModeler::initialize() {
	renderer.initGL(500, 500);
	renderer.setWorld(*world);
	polygonizer = new Vox::MarchingCubes(127);
    addTree(7, 6);
}

void VoxelModeler::draw() {
	renderer.render();
}

void VoxelModeler::handleEvent(int key) {
	cout << "Got: " << key << endl;
}

void VoxelModeler::update(void * context) {
	VoxelModeler * instance = (VoxelModeler *) context;
	instance->display->redraw();
}

