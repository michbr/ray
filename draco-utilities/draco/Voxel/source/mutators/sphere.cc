
#include "mutators/sphere.h"
#include "tree.h"

using namespace std;
using namespace Vox;


SphereMut::SphereMut(const Vector3& pos, double radius, const Voxel& value): pos(pos), radius(radius), value(value) {
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
	if ()
	byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + value.averageOpacity() * (maxDis - dis)) / 2);
	if ((dis - minDis) > 0.5f)
		return new Voxel(value.averageMaterialType(), newOpacity);
	return new Voxel(original.averageMaterialType(), newOpacity);
}

void SphereMut::getBounds(const Tree& target, Index& min, Index& max) const {
	Vector3<double> radiusCube = new Vector3<double>(radius, radius, radius) / target.voxSize;
	Vector3<double> exactMin = (pos -target.pos) /target.voxSize -radiusCube -Vector3<double>(control.voxSize /2, control.voxSize /2, control.voxSize /2);
	Vector3<double> exactMax = exactMin + radiusCube * 2;
	min.depth = target.maxDepth;
	max.depth = target.maxDepth;
	min.x = exactMin.x; min.y = exactMin.y; min.z = exactMin.z;
	max.x = exactMax.x; max.y = exactMax.y; max.z = exactMax.z;
}
