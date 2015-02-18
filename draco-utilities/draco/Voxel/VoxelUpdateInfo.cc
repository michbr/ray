using UnityEngine;
using System.Collections;


namespace Vox {

	public class VoxelUpdateInfo {

		public const byte DIMENSION = 3;
		public byte detailLevel;
		public float size;
		public VoxelHolder[, ,] blocks;
		public VoxelRenderer[, ,] renderers;
		public VoxelControlV2 control;
		public int x, y, z;

		private VoxelUpdateInfo() {
			blocks = new VoxelHolder[DIMENSION, DIMENSION, DIMENSION];
			renderers = new VoxelRenderer[DIMENSION, DIMENSION, DIMENSION];
		}

		public VoxelUpdateInfo(float size, VoxelHolder main, VoxelControlV2 control)
			: this() {
			this.size = size;
			this.detailLevel = 0;
			this.control = control;
			x = y = z = 0;
			for (byte xi = 0; xi < DIMENSION; ++xi) {
				for (byte yi = 0; yi < DIMENSION; ++yi) {
					for (byte zi = 0; zi < DIMENSION; ++zi) {
						blocks[xi, yi, zi] = Voxel.empty;
					}
				}
			}
			blocks[1, 1, 1] = main;
		}

		public VoxelUpdateInfo(VoxelUpdateInfo super, byte xi, byte yi, byte zi)
			: this() {
			size = super.size / VoxelBlock.CHILD_DIMENSION;
			detailLevel = (byte)(super.detailLevel + 1);
			control = super.control;
			x = super.x * VoxelBlock.CHILD_DIMENSION + xi;
			y = super.y * VoxelBlock.CHILD_DIMENSION + yi;
			z = super.z * VoxelBlock.CHILD_DIMENSION + zi;
			for (byte xii = 0; xii < DIMENSION; ++xii) {
				for (byte yii = 0; yii < DIMENSION; ++yii) {
					for (byte zii = 0; zii < DIMENSION; ++zii) {
						blocks[xii, yii, zii] = super.getSub(VoxelBlock.CHILD_COUNT_POWER, (byte)(xii + xi + VoxelBlock.CHILD_DIMENSION - 1), (byte)(yii + yi + VoxelBlock.CHILD_DIMENSION - 1), (byte)(zii + zi + VoxelBlock.CHILD_DIMENSION - 1));
						renderers[xii, yii, zii] = super.renderers[(int)((xii + xi + 1) * 0.5), (int)((yii + yi + 1) * 0.5), (int)((zii + zi + 1) * 0.5)];
						if (renderers[xii, yii, zii] == null || renderers[xii, yii, zii].old) {
							renderers[xii, yii, zii] = super.blocks[(int)((xii + xi + 1) * 0.5), (int)((yii + yi + 1) * 0.5), (int)((zii + zi + 1) * 0.5)].getRenderer(0, 0, 0, 0);
							if (renderers[xii, yii, zii] == null || renderers[xii, yii, zii].old)
								renderers[xii, yii, zii] = blocks[xii, yii, zii].getRenderer(0, 0, 0, 0);
							if (renderers[xii, yii, zii] != null && renderers[xii, yii, zii].old)
								renderers[xii, yii, zii] = null;
						}
					}
				}
			}
		}

		public VoxelUpdateInfo getSubInfo(byte detail, int xi, int yi, int zi) {
			if (detail < 1) return this;
			int dimension = 1 << (detail - 1);
			return new VoxelUpdateInfo(this, (byte)(xi / dimension), (byte)(yi / dimension), (byte)(zi / dimension)).getSubInfo((byte)(detail - 1), xi % dimension, yi % dimension, zi % dimension);
		}

		public void setFromSister(VoxelUpdateInfo sister, byte xi, byte yi, byte zi) {
			size = sister.size;
			detailLevel = sister.detailLevel;
			control = sister.control;
			x = sister.x + xi - 1;
			y = sister.y + yi - 1;
			z = sister.z + zi - 1;
			for (byte xii = (byte)(1 - (xi + 1) / 2); xii < DIMENSION - (xi / 2); ++xii) {
				for (byte yii = (byte)(1 - (yi + 1) / 2); yii < DIMENSION - (yi / 2); ++yii) {
					for (byte zii = (byte)(1 - (zi + 1) / 2); zii < DIMENSION - (zi / 2); ++zii) {
						blocks[xii, yii, zii] = sister.blocks[xii + xi - 1, yii + yi - 1, zii + zi - 1];
						renderers[xii, yii, zii] = sister.renderers[xii + xi - 1, yii + yi - 1, zii + zi - 1];
					}
				}
			}
		}

		public bool isSolid() {
			for (byte xi = 0; xi < DIMENSION; ++xi) {
				for (byte yi = 0; yi < DIMENSION; ++yi) {
					for (byte zi = 0; zi < DIMENSION; ++zi) {
						if (blocks[xi, yi, zi].GetType() != typeof(Voxel) ||
							(blocks[xi, yi, zi].averageOpacity() >= control.isoLevel ^ blocks[xi, yi, zi].averageOpacity() >= control.isoLevel))
							return false;
					}
				}
			}
			return true;
		}

		public VoxelHolder getSub(byte detailLevel, int x, int y, int z) {
			int dimension = 1 << detailLevel;
			return blocks[x / dimension, y / dimension, z / dimension].get(detailLevel, x % dimension, y % dimension, z % dimension);
		}

		public override string ToString() {
			return "detail: " + this.detailLevel + ", size: " + this.size + ", position: " + x + ", " + y + ", " + z;
		}
	}

}