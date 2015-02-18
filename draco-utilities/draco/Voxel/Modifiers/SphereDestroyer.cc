using UnityEngine;
using System.Collections;

namespace Vox {
	public class SphereDestroyer : SphereModifier {

		public float maximumStrength;
		public bool variableDestruction;
		
		private SphereDestroyer(VoxelControlV2 control, Vector3 worldPosition, float worldRadius, VoxelHolder value, bool updateMesh)
			: base(control, worldPosition, worldRadius, value, updateMesh) {
		}

		public SphereDestroyer(VoxelControlV2 control, Vector3 worldPosition, float worldRadius, VoxelHolder value, float maximumStrength, bool variableDestruction, bool updateMesh)
			: this(control, worldPosition, worldRadius, value, updateMesh) {

		}


		protected override VoxelHolder modifyVoxel(VoxelHolder original, int x, int y, int z) {
			VoxelMaterial targetMaterial = control.voxelMaterials[original.averageMaterialType()];
			if (targetMaterial.strength > maximumStrength) return original;
			Vector3 center = (min + max) / 2;
			float radius;
			if (variableDestruction)
				radius = (center.x - min.x) * (1 - targetMaterial.strength / maximumStrength);
			else
				radius = center.x - min.x;
			float minDis = (radius - 1);
			float maxDis = (radius + 1);
			float dis = (center - new Vector3(x, y, z)).magnitude;
			if (dis > maxDis)
				return original;
			if (dis < minDis)
				return value;
			byte newOpacity = (byte)((original.averageOpacity() * (dis - minDis) + value.averageOpacity() * (maxDis - dis)) / 2);
			if ((dis - minDis) > 0.5f)
				return new Voxel(original.averageMaterialType(), newOpacity);
			return new Voxel(original.averageMaterialType(), newOpacity);
		}

	}
}
