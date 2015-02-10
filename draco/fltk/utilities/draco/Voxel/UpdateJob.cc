using UnityEngine;
using System.Collections;

namespace Vox {

	public class GenMeshJob : VoxelJob {

		public int xOff, yOff, zOff;
		public byte detailLevel;
		private VoxelBlock block;
		private VoxelControlV2 control;

		public GenMeshJob(VoxelBlock block, VoxelControlV2 control, byte detailLevel) {
			this.block = block;
			this.control = control;
			this.detailLevel = detailLevel;
		}

		public override void execute() {
			lock (control) {
				VoxelUpdateInfo info = control.getBaseUpdateInfo().getSubInfo(detailLevel, xOff, yOff, zOff);
				getRenderer().genMesh(info);
			}
		}

		public VoxelBlock getBlock() {
			return block;
		}

		public VoxelRenderer getRenderer() {
			return block.getRenderer(0, 0, 0, 0);
		}

		public void setOffset(int xOff, int yOff, int zOff) {
			this.xOff = xOff;
			this.yOff = yOff;
			this.zOff = zOff;
		}
	}

	public class ApplyMeshJob : VoxelJob {

		private VoxelRenderer rend;
		private byte detailLevel;
		private int x, y, z;

		public ApplyMeshJob(VoxelRenderer rend, byte detailLevel, int x, int y, int z) {
			//MonoBehaviour.print("CREATING!");
			this.rend = rend;
			this.detailLevel = detailLevel;
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public override void execute() {
			//MonoBehaviour.print("APPLYING!");
			Vector3 pos = rend.position / rend.size;
			if (rend.parent.isRenderLod(pos.x, pos.y, pos.z, rend.size, rend.control) || rend.parent.isRenderSize(rend.size, rend.control))
				rend.applyMesh(detailLevel, x, y, z);
		}
	}

	public class UpdateCheckJob : VoxelJob {

		public byte xOff, yOff, zOff;
		public byte detailLevel;
		private VoxelBlock block;
		private VoxelControlV2 control;
		
		public UpdateCheckJob(VoxelBlock block, VoxelControlV2 control, byte detailLevel) {
			this.block = block;
			this.control = control;
			this.detailLevel = detailLevel;
			control.addUpdateCheckJob();
		}

		public override void execute() {
			lock (control) {
				block.updateAll(xOff, yOff, zOff, detailLevel, control);
				control.removeUpdateCheckJob();
			}
		}

		public void setOffset(byte xOff, byte yOff, byte zOff) {
			this.xOff = xOff;
			this.yOff = yOff;
			this.zOff = zOff;
		}
	}

	public class DropRendererJob : VoxelJob {

		private VoxelRenderer rend;
		
		public DropRendererJob(VoxelRenderer rend) {
			this.rend = rend;
		}

		public override void execute() {
			lock (rend.control) {
				rend.clear();
			}
		}
	}

}
