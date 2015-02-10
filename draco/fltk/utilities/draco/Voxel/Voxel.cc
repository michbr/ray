using UnityEngine;
using System.Collections;

namespace Vox {

	[System.Serializable]
	public class Voxel : VoxelHolder {

		public static readonly Voxel empty = new Voxel(0, 0);

		public readonly byte opacity;
		public readonly byte matType;

		public Voxel(byte materialType, byte opacity) {
			this.matType = materialType;
			this.opacity = opacity;
		}

		public Voxel(Voxel other) {
			this.matType = other.matType;
			this.opacity = other.opacity;
		}

		public override byte detail() {
			return 0;
		}

		public override byte averageOpacity() {
			return opacity;
		}

		public override byte averageMaterialType() {
			return matType;
		}

		public override VoxelHolder get(byte detailLevel, int x, int y, int z) {
			return this;
		}

		public override VoxelRenderer getRenderer(byte detailLevel, int x, int y, int z) {
			return null;
		}

		public static VoxelHolder setSphere(VoxelHolder original, int x, int y, int z, Vector3 min, Vector3 max, VoxelHolder val) {
			Vector3 center = (min + max) / 2;
			float radius = center.x - min.x;
			float minDis = (radius - 1);
			float maxDis = (radius + 1);
			float dis = (center - new Vector3(x, y, z)).magnitude;
			if (dis > maxDis)
				return original;
			if (dis < minDis)
				return val;
			byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + val.averageOpacity() * (maxDis - dis)) /2);
			if ((dis - minDis) > 0.5f)
				return new Voxel(val.averageMaterialType(), newOpacity);
			return new Voxel(original.averageMaterialType(), newOpacity);
		}

		public override Voxel toVoxel() {
			return this;
		}

	}

}