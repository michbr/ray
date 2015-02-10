using UnityEngine;
using System.Collections;


namespace Vox {

	[AddComponentMenu("Scripts/Voxel/VoxelEditor")]
	public class VoxelEditor : VoxelTerrain {

		public bool useHeightmap;
		public Texture2D[] heightmaps;
		public byte[] heightmapMaterials;

		public void Awake() {
			if (Application.isPlaying) {
				init();
			}
		}

		public void init() {
			if (useHeightmap)
				initializeHeightmap();
			else
				initialize();
		}

		public override void loadData() {
			int voxels = heightmap.height;

			for (int index = 0; index < heightmaps.Length; ++index ) {
				float[,] map = new float[voxels, voxels];
				for (int i = 0; i < heightmaps[index].height; i++) {
					for (int j = 0; j < heightmaps[index].width; j++) {
						Color pix = heightmaps[index].GetPixel((heightmap.height - 1) - i, j);
						map[j, i] = ((pix.r + pix.g + pix.b) / 3.0f) * voxels;
					}
				}
				head.setToHeightmap(maxDetail, 0, 0, 0, ref map, heightmapMaterials[index], this);
			}
		}
	}
}