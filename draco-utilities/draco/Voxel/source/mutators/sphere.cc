
#include "mutators/sphere.h"
#include "tree.h"
#include <cmath>

using namespace std;
using namespace Vox;


SphereMut::SphereMut(const Vector3<double>& pos, double radius, const Voxel& value): pos(pos), radius(radius), value(value) {
//	this.value = value;
//	Vector3 radiusCube = new Vector3(worldRadius, worldRadius, worldRadius) / control.voxelSize();
//	min = control.transform.InverseTransformPoint(worldPosition) / control.voxelSize() - radiusCube - Vector3.one * (control.voxelSize() / 2);
//	max = min + radiusCube * 2;
//	apply();
}


Mutator::Action SphereMut::mutate(Application* app, const Index& voxelPos, byte index, Node& parent) const {
	SphereApplication* sApp = (SphereApplication*) app;
	double voxelSize = app->tree->size / (1 << voxelPos.depth);
	double disSqr = (pos -Vector3<double>(voxelPos.x +0.5, voxelPos.y +0.5, voxelPos.z +0.5) *voxelSize).magnitudeSquared();
//	cout << "checking mutate?" << endl;
	double maxRadius = radius +voxelSize *0.75;
	double maxRadSqr = maxRadius *maxRadius;
//	cout << voxelSize << endl;
//	cout << disSqr << endl;
//	cout << maxRadSqr << endl;
	if (disSqr > maxRadSqr)
		return Action(false, false);
	//	cout << "YO!!! Hello there!" << sApp->maxRadius << endl;
	double minRadius = radius -voxelSize *0.75;
	double minRadSqr = minRadius *minRadius;
//	cout << minRadSqr << endl;
	if (disSqr < minRadSqr) {
		parent.set(index, value);
		return Action(false, true);
	}
	if (voxelPos.depth < app->tree->maxDepth)
		return Action(true, false);
//	cout << "setting something?" << endl;
	double dis = sqrt(disSqr);
	byte newOpacity = (byte)((parent.getOpacity(index) * (dis -minRadius) + value.opacity * (maxRadius - dis)) / 2);
	if ((dis - minRadius) > 0.5f)
		parent.set(index, Voxel(value.material, newOpacity));
	else
		parent.set(index, Voxel(parent.getMaterial(index), newOpacity));
	return Action(false, true);
}

Mutator::Application* SphereMut::setup(Tree& target) const {
	Vector3<double> radiusCube = Vector3<double>(radius, radius, radius) / target.voxSize;
//	cout << "radius: " << radiusCube << endl;
	Vector3<double> exactMin = (pos -target.pos) /target.voxSize -radiusCube -Vector3<double>(target.voxSize /2, target.voxSize /2, target.voxSize /2);
	Vector3<double> exactMax = exactMin + radiusCube * 2.0;
	SphereApplication* app = new SphereApplication();
	app->tree = &target;
	app->min = Index(target.maxDepth, exactMin.x, exactMin.y, exactMin.z);
	app->max = Index(target.maxDepth, exactMax.x, exactMax.y, exactMax.z);
	app->minRadius = radius /target.voxSize -1;
	app->minRadSqr = app->minRadius *app->minRadius;
	app->maxRadius = radius /target.voxSize +1;
	app->maxRadSqr = app->maxRadius *app->maxRadius;
	return app;
}
