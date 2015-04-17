
#include "mutators/sphere.h"
#include "tree.h"

using namespace std;
using namespace Vox;


SphereMut::SphereMut(const Vector3<double>& pos, double radius, const Voxel& value): pos(pos), radius(radius), value(value) {
//	this.value = value;
//	Vector3 radiusCube = new Vector3(worldRadius, worldRadius, worldRadius) / control.voxelSize();
//	min = control.transform.InverseTransformPoint(worldPosition) / control.voxelSize() - radiusCube - Vector3.one * (control.voxelSize() / 2);
//	max = min + radiusCube * 2;
//	apply();
}


bool SphereMut::mutate(Application* app, const Index& voxelPos, byte index, Node& parent) const {
	SphereApplication* sApp = (SphereApplication*) app;
	double dis = (pos -Vector3<double>(voxelPos.x, voxelPos.y, voxelPos.z)).magnitude();
	if (dis > sApp->maxRadius)
		return false;
	if (dis < sApp->minRadius) {
		parent.set(index, value);
		return false;
	}
	byte newOpacity = (byte)((parent.getOpacity(index) * (dis -sApp->minRadius) + value.opacity * (sApp->maxRadius - dis)) / 2);
	if ((dis - sApp->minRadius) > 0.5f)
		parent.set(index, Voxel(value.material, newOpacity));
    else
        parent.set(index, Voxel(parent.getMaterial(index), newOpacity));
    return true;
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
}
