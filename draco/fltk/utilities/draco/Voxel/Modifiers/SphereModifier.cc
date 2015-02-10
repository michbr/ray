using UnityEngine;
using System.Collections;

namespace Vox {

	public class SphereModifier : Modifier {

		public VoxelHolder value;

		public SphereModifier(VoxelControlV2 control, Vector3 worldPosition, float worldRadius, VoxelHolder value, bool updateMesh)
			: base(control, updateMesh) {
			this.value = value;
			Vector3 radiusCube = new Vector3(worldRadius, worldRadius, worldRadius) / control.voxelSize();
			min = control.transform.InverseTransformPoint(worldPosition) / control.voxelSize() - radiusCube - Vector3.one * (control.voxelSize() / 2);
			max = min + radiusCube * 2;
			apply();
		}


		protected override VoxelHolder modifyVoxel(VoxelHolder original, int x, int y, int z) {
			Vector3 center = (min + max) / 2;
			float radius = center.x - min.x;
			float minDis = (radius - 1);
			float maxDis = (radius + 1);
			float dis = (center - new Vector3(x, y, z)).magnitude;
			if (dis > maxDis)
				return original;
			if (dis < minDis)
				return value;
			byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + value.averageOpacity() * (maxDis - dis)) / 2);
			if ((dis - minDis) > 0.5f)
				return new Voxel(value.averageMaterialType(), newOpacity);
			return new Voxel(original.averageMaterialType(), newOpacity);
		}

	}
}
