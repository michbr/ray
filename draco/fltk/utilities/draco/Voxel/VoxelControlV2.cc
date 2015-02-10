using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

namespace Vox {

	[AddComponentMenu("Scripts/Voxel/VoxelControlV2")]
	[ExecuteInEditMode]
	public class VoxelControlV2 : MonoBehaviour {

		// basic stats
		public float BaseSize = 16;
		public byte maxDetail = 6;
		public byte isoLevel = 127;
		public float lodDetail = 1;
		public bool useLod = true;
		public GameObject trees;
		public float treeDensity = 0.02f;
		public float treeSlopeTolerance = 5;
		[HideInInspector]
		public Camera cam;
		public float curLodDetail = 10f;
		public VoxelMaterial[] voxelMaterials;
		public float maxChange;
		public bool createColliders = true;

		// performance stats
		private int treeCount = 0;

		// voxel data
		[HideInInspector]
		public VoxelBlock head;
		[HideInInspector]
		public float[] sizes;
		//[HideInInspector]
		public List<VoxelRenderer> chunks = new List<VoxelRenderer>();
		//private Queue<VoxelJob> updateCheckQueue = new Queue<VoxelJob>(200);
		private Queue<VoxelJob> jobQueue = new Queue<VoxelJob>(100);
		//private Queue<VoxelUpdateJob> updateQueue = new Queue<VoxelUpdateJob>(100);
		private Vector3 localCamPosition;
		private int updateCheckJobs;



		// test values
		private int updateThing = 0;

		public virtual void initialize() {

			float starttime = Time.realtimeSinceStartup;

			// setup lookup tables, etc.
			sizes = new float[maxDetail + 1];
			float s = BaseSize;
			for (int i = 0; i <= maxDetail; ++i) {
				sizes[i] = s;
				s /= 2;
			}
			cam = GameObject.FindGameObjectWithTag("Player").GetComponentInChildren<Camera>();
			if (Application.isPlaying && GetComponent<MineVoxelEvent>() == null)
				gameObject.AddComponent<MineVoxelEvent>();
			updateCheckJobs = 0;
			cam = GameObject.FindGameObjectWithTag("MainCamera").GetComponent<Camera>();

			// initialize voxels
			head = new VoxelBlock();
			genData(0);

			applyRenderers();

			updateLocalCamPosition();

			enqueueCheck(new UpdateCheckJob(head, this, 0));

			float endtime = Time.realtimeSinceStartup;


			print("Voxel Gen time:                   " + (endtime - starttime));
			print("Average Voxel Opacity:            " + head.averageOpacity());
			print("Total Voxel Blocks:               " + VoxelHolder.blockCount);
			print("Total Tree Count:                 " + treeCount);
			print("Renderer Count:                   " + VoxelRenderer.rendCount);
			print("Duplicate Triangle Count:         " + VoxelRenderer.duplicateTriangleCount);
		}

		public void Update() {
			if (Application.isPlaying) {
				if (updateThing == 0) {
					if (useLod) {
						if (curLodDetail < lodDetail) {
							if (lodDetail - curLodDetail < 0.1f) {
								if (lodDetail - curLodDetail > -0.1f)
									curLodDetail = lodDetail;
								else
									curLodDetail -= 0.1f;
							} else
								curLodDetail += 0.1f;
						}
						updateLocalCamPosition();
					}
					if (updateCheckJobs < 1)
						enqueueCheck(new UpdateCheckJob(head, this, 0));
				}
				updateThing = (updateThing + 1) % 2;
			}
			applyQueuedMeshes();
		}

		public void enqueueCheck(VoxelJob job) {
			VoxelThread.enqueueUpdate(job);
			//enqueueJob(job);
		}

		public void enqueueUpdate(VoxelJob job) {
			VoxelThread.enqueueUpdate(job);
			//enqueueJob(job);
		}

		public void applyQueuedMeshes() {
			lock (this) {
				while (jobQueue.Count > 0) {
					jobQueue.Dequeue().execute();
				}
			}
		}

		public float subtractSphere(Vector3 worldLocation, float radius) {

			//Vector3 radiusCube = new Vector3(radius, radius, radius) / sizes[maxDetail];
			//Vector3 min = transform.InverseTransformPoint(worldLocation) / sizes[maxDetail] - radiusCube - Vector3.one * (sizes[maxDetail] / 2);
			//Vector3 max = min + radiusCube * 2;
			//MonoBehaviour.print(min + ", " + max);
			//head.setSphere(getBaseUpdateInfo(), maxDetail, min, max, Voxel.empty, this);
			new SphereModifier(this, worldLocation, radius, new Voxel(0, 0), true);

			return 0;
		}

		public float getLodDetail() {
			return curLodDetail;
		}

		public VoxelBlock getHead() {
			return head;
		}

		public void updateLocalCamPosition() {
			localCamPosition = transform.TransformPoint(cam.transform.position);
		}

		public Vector3 getLocalCamPosition() {
			return localCamPosition;
		}

		public VoxelUpdateInfo getBaseUpdateInfo() {
			return new VoxelUpdateInfo(sizes[0], head, this);
		}

		public float voxelSize() {
			return sizes[maxDetail];
		}

		internal void addUpdateCheckJob() {
			++updateCheckJobs;
		}

		internal void removeUpdateCheckJob() {
			--updateCheckJobs;
		}

		// this functions sets the values of the voxels, doing all of the procedural generation work
		// currently it just uses a "height map" system.  This is fine for initial generation, but
		// then more passes need to be done for cliffs, caves, streams, etc.
		protected virtual void genData(int seed) {

			// the following makes a hollow sphere
			//int dimension = 1 << maxDetail;
			//Vector3 min = new Vector3(0, 0, 0);
			//Vector3 max = new Vector3(dimension - 4, dimension - 4, dimension - 4);
			//head.set(new Voxel(0, byte.MaxValue));
			//head.setSphere(new VoxelBlock.UpdateInfo(sizes[0], head, this),
			//	0, 0, 0, maxDetail, min, max, new Voxel(0, 0));

			// the following generates terrain from a height map
			UnityEngine.Random.seed = seed;
			int dimension = 1 << maxDetail;
			float acceleration = 0;
			float height = dimension * 0.6f;
			float[,] heightMap = new float[dimension, dimension];
			float[,] accelMap = new float[dimension, dimension];
			byte[,] matMap = new byte[dimension, dimension];
			for (int x = 0; x < dimension; ++x) {
				for (int z = 0; z < dimension; ++z) {
					matMap[x, z] = (byte)UnityEngine.Random.Range(0, voxelMaterials.Length);

					// calculate the height
					if (x != 0) {
						if (z == 0) {
							height = heightMap[x - 1, z];
							acceleration = accelMap[x - 1, z];
						} else {
							height = (heightMap[x - 1, z] + heightMap[x, z - 1]) / 2;
							acceleration = (accelMap[x - 1, z] + accelMap[x, z - 1]) / 2;
						}
					}
					float edgeDistance = Mathf.Max(Mathf.Abs(dimension / 2 - x - 10), Mathf.Abs(dimension / 2 - z - 10));
					float edgeDistancePercent = 1 - edgeDistance / (dimension / 2);
					float percent;
					if (edgeDistancePercent < 0.2)
						percent = height / (dimension * 0.6f) - 0.4f;
					else
						percent = height / (dimension * 0.4f);
					float roughness = maxChange + 0.2f * (1 - edgeDistancePercent);
					acceleration += UnityEngine.Random.Range(-roughness * percent, roughness * (1 - percent));
					acceleration = Mathf.Min(Mathf.Max(acceleration, -roughness * 7), roughness * 7);
					height = Mathf.Min(Mathf.Max(height + acceleration, 0), dimension);
					heightMap[x, z] = height;
					accelMap[x, z] = acceleration;
				}
			}
			head.setToHeightmap(maxDetail, 0, 0, 0, ref heightMap, matMap, this);

			// generate trees
			//for (int x = 0; x < dimension; ++x) {
			//	for (int z = 0; z < dimension; ++z) {
			//		if (Random.Range(Mathf.Abs(accelMap[x, z]) / treeSlopeTolerance, 1) < treeDensity) {
			//			GameObject tree = (GameObject)GameObject.Instantiate(trees);
			//			tree.transform.parent = transform;
			//			tree.transform.localPosition = new Vector3(x * size, heightMap[x, z] * size - 1.5f, z * size);
			//			++treeCount;
			//		}
			//	}
			//}
		}

		public void applyRenderers() {
			foreach (VoxelRenderer rend in chunks) {

				rend.control = this;
				if (rend.obs == null || rend.obs.Length < 1) continue;
				int fraction = (int)(BaseSize / rend.size);
				byte detailLevel;
				for (detailLevel = 0; fraction > 1; ++detailLevel)
					fraction >>= 1;
				if (detailLevel >= maxDetail) continue;

				VoxelHolder holder = head.get(detailLevel, (int)(rend.position.x / rend.size), (int)(rend.position.y / rend.size), (int)(rend.position.z / rend.size));
				if (holder.GetType() == typeof(VoxelBlock)) {
					rend.parent = (VoxelBlock) holder;
					rend.parent.renderer = rend;
				}
			}
		}

		public void wipe() {
			for (int i = chunks.Count - 1; i >= 0; --i)
				chunks[i].clear();
			chunks.Clear();

			if (head != null) {
				head.clearSubRenderers(this);
				head = null;
			}
		}

		//public void OnGUI() {
		//	GUI.Label(new Rect(0, 200, 200, 20), "Voxel Triangle Count: " + VoxelRenderer.triangleCount);
		//	GUI.Label(new Rect(0, 220, 200, 20), "Voxel Vertex Count: " + VoxelRenderer.vertexCount);
		//	GUI.Label(new Rect(0, 240, 200, 20), "Voxel Duplicate Triangle Count: " + VoxelRenderer.duplicateTriangleCount);
		//}

		internal void enqueueMeshApply(VoxelJob job) {
			jobQueue.Enqueue(job);
		}

		internal void enqueueJob(VoxelJob job) {
			jobQueue.Enqueue(job);
		}
	}

}