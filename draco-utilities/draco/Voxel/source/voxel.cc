

#include "voxel.h"

using namespace std;
using namespace Vox;

Voxel::Voxel(byte opacity, unsigned short material) :
	opacity(opacity), material(material) {}

Voxel::Voxel(const Voxel& other) :
	opacity(other.opacity), material(other.material) {}


bool Voxel::compact() const {
    return sizeof(this) <= 8;
}
bool Voxel::empty() const {
	return opacity == 0;
}
byte Voxel::average() const {
	return opacity;
}

//public byte detail() {
//	return 0;
//}
//
//public byte averageOpacity() {
//	return opacity;
//}
//
//public byte averageMaterialType() {
//	return matType;
//}
//
//public VoxelHolder get(byte detailLevel, int x, int y, int z) {
//	return this;
//}
//
//public VoxelRenderer getRenderer(byte detailLevel, int x, int y, int z) {
//	return null;
//}
//
//public static VoxelHolder setSphere(VoxelHolder original, int x, int y, int z, Vector3 min, Vector3 max, VoxelHolder val) {
//	Vector3 center = (min + max) / 2;
//	float radius = center.x - min.x;
//	float minDis = (radius - 1);
//	float maxDis = (radius + 1);
//	float dis = (center - new Vector3(x, y, z)).magnitude;
//	if (dis > maxDis)
//		return original;
//	if (dis < minDis)
//		return val;
//	byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + val.averageOpacity() * (maxDis - dis)) /2);
//	if ((dis - minDis) > 0.5f)
//		return new Voxel(val.averageMaterialType(), newOpacity);
//	return new Voxel(original.averageMaterialType(), newOpacity);
//}
//
//public Voxel toVoxel() {
//	return this;
//}

ostream &operator<<(ostream& out, byte value) {
    return out << (unsigned int) value;
}

Voxel Voxel::read(void *address) {
	Voxel voxel(0, 0);
	void **value = ((void**) (&voxel)) +1;
	void **loc = (void**)address;
	*value = *loc;
	return voxel;
}
void Voxel::write(void *address, const Voxel& voxel) {
	void **value = ((void**) (&voxel)) +1;
	void **loc = (void**)address;

//	cout << "voxel: " << &(voxel) << endl;
//	cout << "value: " << (value) << endl;
//	cout << "address: " << (address) << endl;
//	cout << "loc: " << (loc) << endl;

	*loc = *value;
}
