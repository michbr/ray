
#include "mutators/sphere.h"
#include "tree.h"

using namespace std;
using namespace Vox;


SphereMut::SphereMut(const Vector3<double>& pos, double radius, const Voxel& value):
pos(pos), radius(radius), value(value), minRadius(radius -1), minRadSqr(minRadius *minRadius), maxRadius(radius +1), maxRadSqr(maxRadius *maxRadius) {
//	this.value = value;
//	Vector3 radiusCube = new Vector3(worldRadius, worldRadius, worldRadius) / control.voxelSize();
//	min = control.transform.InverseTransformPoint(worldPosition) / control.voxelSize() - radiusCube - Vector3.one * (control.voxelSize() / 2);
//	max = min + radiusCube * 2;
//	apply();
}


bool SphereMut::mutate(const Tree& target, const Index& voxelPos, byte index, Node& parent) const {
	double dis = (pos -Vector3<double>(voxelPos.x, voxelPos.y, voxelPos.z)).magnitude();
	if (dis > maxDis)
		return false;
	if (dis < minDis) {
		parent.set(index, value);
		return false;
	}
	byte newOpacity = (byte)((parent.getOpacity(index) * (dis - minDis) + value.opacity * (maxDis - dis)) / 2);
	if ((dis - minDis) > 0.5f)
		parent.set(index, Voxel(value.material, newOpacity));
    else
        parent.set(index, Voxel(parent.getMaterial(index), newOpacity));
    return true;
}

void SphereMut::getBounds(const Tree& target, Index& min, Index& max) const {
	Vector3<double> radiusCube = Vector3<double>(radius, radius, radius) / target.voxSize;
//	cout << "radius: " << radiusCube << endl;
	Vector3<double> exactMin = (pos -target.pos) /target.voxSize -radiusCube -Vector3<double>(target.voxSize /2, target.voxSize /2, target.voxSize /2);
	Vector3<double> exactMax = exactMin + radiusCube * 2.0;
	min = Index(target.maxDepth, exactMin.x, exactMin.y, exactMin.z);
	max = Index(target.maxDepth, exactMax.x, exactMax.y, exactMax.z);
}
