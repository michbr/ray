
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


bool SphereMut::mutate(const Tree& target, const Index& voxelPos, byte index, Node& parent) const {
	double minDis = (radius - 1);
	double maxDis = (radius + 1);
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
	Vector3<double> exactMin = (pos -target.pos) /target.voxSize -radiusCube -Vector3<double>(target.voxSize /2, target.voxSize /2, target.voxSize /2);
	Vector3<double> exactMax = exactMin + radiusCube * 2.0;
	min.depth = target.maxDepth;
	max.depth = target.maxDepth;
	min.x = exactMin.x; min.y = exactMin.y; min.z = exactMin.z;
	max.x = exactMax.x; max.y = exactMax.y; max.z = exactMax.z;
}
