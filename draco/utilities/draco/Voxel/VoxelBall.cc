using UnityEngine;
using System.Collections;

namespace Vox {
	
	[AddComponentMenu("Scripts/Voxel/VoxelBall")]
	public class VoxelBall : VoxelControlV2 {

		public void Awake() {
			initialize();
		}

		protected override void genData(int seed) {
			//TODO: make it use the new sphere setting method
			//curLodDetail = 100;
			//int dimension = 1 << maxDetail;
			//Vector3 min = new Vector3(0, 0, 0);
			//Vector3 max = new Vector3(dimension - 4, dimension - 4, dimension - 4);
			//new SphereModifier(this, blah, dimension - 4, new Voxel(0, byte.MaxValue), true);
			//head.setSphere(new VoxelUpdateInfo(sizes[0], head, this), maxDetail, min, max, new Voxel(0, byte.MaxValue), this);
		}
	}

}