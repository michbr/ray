

#include "voxel.h"

namespace Vox {

    Atom::Atom(byte opacity, unsigned short material) :
		opacity(opacity), material(material) {}

    Atom::Atom(const Atom& other) :
		opacity(other.opacity), material(other.material) {}


    bool Atom::compact() const {
	    return sizeof(this) <= 8;
    }
	bool Atom::empty() const {
		return opacity == 0;
	}
	byte Atom::average() const {
		return opacity;
	}

//		public override byte detail() {
//			return 0;
//		}
//
//		public override byte averageOpacity() {
//			return opacity;
//		}
//
//		public override byte averageMaterialType() {
//			return matType;
//		}
//
//		public override VoxelHolder get(byte detailLevel, int x, int y, int z) {
//			return this;
//		}
//
//		public override VoxelRenderer getRenderer(byte detailLevel, int x, int y, int z) {
//			return null;
//		}
//
//		public static VoxelHolder setSphere(VoxelHolder original, int x, int y, int z, Vector3 min, Vector3 max, VoxelHolder val) {
//			Vector3 center = (min + max) / 2;
//			float radius = center.x - min.x;
//			float minDis = (radius - 1);
//			float maxDis = (radius + 1);
//			float dis = (center - new Vector3(x, y, z)).magnitude;
//			if (dis > maxDis)
//				return original;
//			if (dis < minDis)
//				return val;
//			byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + val.averageOpacity() * (maxDis - dis)) /2);
//			if ((dis - minDis) > 0.5f)
//				return new Voxel(val.averageMaterialType(), newOpacity);
//			return new Voxel(original.averageMaterialType(), newOpacity);
//		}
//
//		public override Voxel toVoxel() {
//			return this;
//		}


}