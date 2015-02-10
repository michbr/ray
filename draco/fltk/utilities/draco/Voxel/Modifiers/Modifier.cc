using UnityEngine;
using System.Collections;

namespace Vox {

	public abstract class Modifier {

		public VoxelControlV2 control;
		public Vector3 min, max;
		public bool updateMesh;

		protected Modifier(VoxelControlV2 control, bool updateMesh) {
			this.control = control;
			this.updateMesh = updateMesh;
		}

		//protected Modifier(VoxelControlV2 control, Vector3 min, Vector3 max) {
		//	this.control = control;
		//	this.min = min;
		//	this.max = max;
		//}

		protected void apply() {
			traverse(control.getBaseUpdateInfo(), control.maxDetail);
		}

		protected void traverse(VoxelUpdateInfo info, byte detailLevel) {
			int factor = 1 << (detailLevel - VoxelBlock.CHILD_COUNT_POWER);
			byte xiMin = (byte)Mathf.Max(min.x / factor - info.x * VoxelBlock.CHILD_DIMENSION, 0);
			byte xiMax = (byte)Mathf.Min((max.x + 3) / factor - info.x * VoxelBlock.CHILD_DIMENSION, VoxelBlock.CHILD_DIMENSION - 1);
			byte yiMin = (byte)Mathf.Max(min.y / factor - info.y * VoxelBlock.CHILD_DIMENSION, 0);
			byte yiMax = (byte)Mathf.Min((max.y + 3) / factor - info.y * VoxelBlock.CHILD_DIMENSION, VoxelBlock.CHILD_DIMENSION - 1);
			byte ziMin = (byte)Mathf.Max(min.z / factor - info.z * VoxelBlock.CHILD_DIMENSION, 0);
			byte ziMax = (byte)Mathf.Min((max.z + 3) / factor - info.z * VoxelBlock.CHILD_DIMENSION, VoxelBlock.CHILD_DIMENSION - 1);

			VoxelBlock block = (VoxelBlock)info.blocks[1, 1, 1];

			for (byte xi = xiMin; xi <= xiMax; ++xi) {
				for (byte yi = yiMin; yi <= yiMax; ++yi) {
					for (byte zi = ziMin; zi <= ziMax; ++zi) {
						if (detailLevel <= VoxelBlock.CHILD_COUNT_POWER) {
							block.children[xi, yi, zi] = modifyVoxel(block.children[xi, yi, zi], info.x * VoxelBlock.CHILD_DIMENSION + xi, info.y * VoxelBlock.CHILD_DIMENSION + yi, info.z * VoxelBlock.CHILD_DIMENSION + zi);
						} else {
							if (block.children[xi, yi, zi].GetType() == typeof(Voxel)) {
								block.children[xi, yi, zi] = new VoxelBlock((Voxel)block.children[xi, yi, zi]);
							}
							traverse(new VoxelUpdateInfo(info, xi, yi, zi), (byte)(detailLevel - VoxelBlock.CHILD_COUNT_POWER));
						}
					}
				}
			}

			// TODO: this should check if completely contained, not if rendersize (for distant modifications) - FIXED?
			if (updateMesh && info != null && (block.isRenderSize(info.size, control) || block.isRenderLod(info.x, info.y, info.z, control.sizes[detailLevel], control))) {
				block.updateAll(info.x, info.y, info.z, info.detailLevel, control, true);
			}
		}

		protected abstract VoxelHolder modifyVoxel(VoxelHolder original, int x, int y, int z);

	}
}
