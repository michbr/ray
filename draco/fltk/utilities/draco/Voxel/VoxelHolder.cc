using UnityEngine;
using System.Collections;

namespace Vox {

	public abstract class VoxelHolder {

		public static int blockCount = 0;

		// returns how many more layers there are beneath this one
		public abstract byte detail();

		public abstract byte averageOpacity();

		public abstract byte averageMaterialType();

		// relative to me.  detail level 1 means go one further, no matter what. index also relative to me
		public abstract VoxelHolder get(byte detailLevel, int x, int y, int z);

		public abstract VoxelRenderer getRenderer(byte detailLevel, int x, int y, int z);

		public abstract Voxel toVoxel();

		public static bool operator ==(VoxelHolder v1, VoxelHolder v2) {
			if (System.Object.ReferenceEquals(v1, v2))
				return true;
			if (((object)v1 == null) || ((object)v2 == null))
				return false;
			return (v1.averageMaterialType() == v2.averageMaterialType() && v1.averageOpacity() == v2.averageOpacity());
		}

		public static bool operator !=(VoxelHolder v1, VoxelHolder v2) {
			return !(v1 == v2);
		}

	}

}