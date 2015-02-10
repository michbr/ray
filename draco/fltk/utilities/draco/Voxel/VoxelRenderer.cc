using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

namespace Vox {

	[ExecuteInEditMode]
	[System.Serializable]
	public class VoxelRenderer {

		public static int rendCount = 0;
		public static int vertexCount = 0;
		public static int triangleCount = 0;
		public static int duplicateTriangleCount = 0;

		public const byte VOXEL_COUNT_POWER = 4;
		public const byte VOXEL_DIMENSION = 1 << VOXEL_COUNT_POWER;
		public const byte VERTEX_DIMENSION = VOXEL_DIMENSION + 2;
		public const float NORMAL_SMOOTHNESS = 0.1f; // 0 - 1

		public Dictionary<int, object> vertices;
		public Dictionary<int, byte> vertexMaterials;
		[System.NonSerialized]
		public VoxelBlock parent;
		[System.NonSerialized]
		public VoxelControlV2 control;
		public MeshCollider collider;
		public float size;
		public Vector3 position;
		public byte xDim, yDim, zDim;
		public byte xExtend, yExtend, zExtend;
		public GameObject[] obs;
		public Vector3[] VERTS, NORMS;
		//public byte[] MATS;
		public int[] TRIS;
		public bool applied = false;
		public bool old = false;


		public void clear() {
			lock (this) {
				if (control != null)
					control.chunks.Remove(this);
				removePolyCount();
				if (obs != null)
					foreach (GameObject ob in obs) {
						GameObject.DestroyImmediate(ob);
					}
				if (collider != null)
					GameObject.DestroyImmediate(collider);
				if (parent != null) {
					parent.renderer = null;
					parent = null;
				}
			}
		}

		public VoxelRenderer(VoxelBlock parent, VoxelControlV2 control, Vector3 localPosition) {
			this.parent = parent;
			this.position = localPosition;
			this.control = control;
			size = 0;
			++rendCount;
			VERTS = new Vector3[0];
			NORMS = new Vector3[0];
			TRIS = new int[0];
			control.chunks.Add(this);
		}

		public VoxelBlock getBlock() {
			return parent;
		}

		public void genMesh(VoxelUpdateInfo info) {
			size = info.size;

			Queue<int[]> triangleSet = new Queue<int[]>();
			vertices = new Dictionary<int, object>();
			vertexMaterials = new Dictionary<int, byte>();
			Voxel[, ,] voxels = createVoxelArray(info);
			MarchingCubesV2.setup(info.size / VOXEL_DIMENSION, control.isoLevel, ref vertices, ref vertexMaterials, ref voxels, position - new Vector3(0.5f, 0.5f, 0.5f) * size / VOXEL_DIMENSION, null);
			int totalTris = 0;

			for (byte x = (byte)(1 - xExtend), x1 = (byte)(x + 1); x1 < xDim; x = x1++) {
				for (byte y = (byte)(1 - yExtend), y1 = (byte)(y + 1); y1 < yDim; y = y1++) {
					for (byte z = (byte)(1 - zExtend), z1 = (byte)(z + 1); z1 < zDim; z = z1++) {
						lock (control) {
							VoxelHolder block = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION + x, VOXEL_DIMENSION + y, VOXEL_DIMENSION + z);
							voxels[x1, y1, z1] = block.toVoxel();
							int[] tris = MarchingCubesV2.lookupTriangles(x, y, z, x1, y1, z1);
							if (tris == null) continue;
							triangleSet.Enqueue(tris);
							totalTris += tris.Length;
						}
					}
				}
			}

			if (vertices.Count < 1) {
				applied = true;
				return;
			}


			List<int> triangles = new List<int>();
			List<Vector3> finalVertices = new List<Vector3>(vertices.Count);
			//List<byte> finalMats = new List<byte>(vertices.Count);
			while (triangleSet.Count > 0) {
				int[] triangleList = triangleSet.Dequeue();
				for (int i = 0; i < triangleList.Length; ++i) {
					if (vertices[triangleList[i]].GetType() == typeof(Vector3)) {
						finalVertices.Add((Vector3)vertices[triangleList[i]]);
						//finalMats.Add(vertexMaterials[triangleList[i]]);
						vertices[triangleList[i]] = finalVertices.Count - 1;
					}
					triangles.Add((int)vertices[triangleList[i]]);
				}
			}
			VERTS = finalVertices.ToArray();
			TRIS = triangles.ToArray();
			//MATS = finalMats.ToArray();
			calcNorms();

			alignEdge(info, 0, 1, 1);
			alignEdge(info, 2, 1, 1);
			alignEdge(info, 1, 0, 1);
			alignEdge(info, 1, 2, 1);
			alignEdge(info, 1, 1, 0);
			alignEdge(info, 1, 1, 2);
			lock (control) {
				control.enqueueMeshApply(new ApplyMeshJob(this, info.detailLevel, info.x, info.y, info.z));
			}

		}

		public void applyMesh(byte detailLevel, int x, int y, int z) {
			applied = true;
			if (TRIS.Length < 1 && (obs == null || obs.Length < 1))
				return;

			removePolyCount();

			if (control.createColliders) {
				if (collider == null) {
					Mesh m = new Mesh();
					m.MarkDynamic();
					collider = control.gameObject.AddComponent<MeshCollider>();
					collider.sharedMesh = m;
					collider.hideFlags = HideFlags.HideInInspector;
				}
				Mesh colMesh = collider.sharedMesh;

				colMesh.triangles = null;
				colMesh.normals = null;
				colMesh.vertices = VERTS;
				colMesh.normals = NORMS;
				colMesh.triangles = TRIS;
				colMesh.RecalculateBounds();
				colMesh.Optimize();
			}

			Dictionary<byte, Dictionary<int, int>> materialVertices = new Dictionary<byte, Dictionary<int, int>>();
			byte[] MATS = new byte[VERTS.Length];
			foreach (int index in vertices.Keys) {
				if (vertexMaterials.ContainsKey(index)) {
					byte material = vertexMaterials[index];
					MATS[(int)vertices[index]] = material;
					if (!materialVertices.ContainsKey(material))
						materialVertices[material] = new Dictionary<int, int>();
					materialVertices[material][(int)vertices[index]] = materialVertices[material].Count;
				}
			}

			GameObject[] oldObs = obs;
			obs = new GameObject[materialVertices.Count];
			if (oldObs != null && oldObs.Length > obs.Length) {
				Array.Copy(oldObs, obs, obs.Length);
				for (int i = obs.Length; i < oldObs.Length; ++i) {
					GameObject.Destroy(oldObs[i]);
				}
			} else {
				if (oldObs != null)
					Array.Copy(oldObs, obs, oldObs.Length);
				for(int i=(oldObs==null)?0:oldObs.Length; i<obs.Length; ++i) {
					obs[i] = new GameObject("Voxel Section");
					obs[i].transform.parent = control.transform;
					obs[i].transform.localPosition = Vector3.zero;
					obs[i].AddComponent<MeshRenderer>().enabled = false;
					obs[i].AddComponent<MeshFilter>().sharedMesh = new Mesh();
				}
			}

			List<int>[] tris = new List<int>[byte.MaxValue];
			foreach(byte key in materialVertices.Keys)
				tris[key] = new List<int>(TRIS.Length /obs.Length);
			for(int i=0; i<TRIS.Length; i+=3) {
				List<byte> prevMats = new List<byte>(3);
				for (int j = 0; j < 3; ++j) {
					byte mat = MATS[TRIS[i + j]];
					if (!prevMats.Contains(mat)) {
						Dictionary<int, int> matVerts = materialVertices[mat];
						for (int k = 0; k < 3; ++k) {
							int vert = TRIS[i + k];
							if (!matVerts.ContainsKey(vert))
								matVerts[vert] = matVerts.Count;
							tris[mat].Add(matVerts[vert]);
						}
						prevMats.Add(mat);
					}
				}
			}

			int obIndex = 0;
			foreach (byte material in materialVertices.Keys) {
				Dictionary<int, int> matVerts = materialVertices[material];
				Vector3[] verts = new Vector3[matVerts.Count];
				Vector3[] norms = new Vector3[matVerts.Count];
				Vector2[] uvs = new Vector2[matVerts.Count];
				foreach (int index in matVerts.Keys) {
					int i = matVerts[index];
					norms[i] = NORMS[index];
					if (MATS[index] < material) {
						verts[i] = VERTS[index] +norms[i] * 0.01f *Mathf.Pow(size, 1.5f) /VOXEL_DIMENSION;
						uvs[i] = Vector2.zero;
					} else if (MATS[index] > material) {
						verts[i] = VERTS[index];// -norms[i] * 0.01f * size / VOXEL_DIMENSION;
						uvs[i] = Vector2.up;
					} else {
						verts[i] = VERTS[index];
						uvs[i] = Vector2.up;
					}
				}

				Mesh m = obs[obIndex].GetComponent<MeshFilter>().sharedMesh;
				m.triangles = null;
				m.normals = null;
				m.uv = null;
				m.vertices = null;
				m.vertices = verts;
				m.normals = norms;
				m.uv = uvs;
				m.triangles = tris[material].ToArray();
				m.RecalculateBounds();
				m.Optimize();
				MeshRenderer rend = obs[obIndex].GetComponent<MeshRenderer>();
				rend.sharedMaterial = control.voxelMaterials[material].renderMaterial;
				rend.sharedMaterial.renderQueue = material;
				rend.enabled = true;
				++obIndex;
			}



			addPolyCount();
			//obs[0].GetComponent<MeshRenderer>().enabled = true;
			if (control.createColliders) {
				collider.enabled = false;
				if (parent.isRenderSize(size, control))
					collider.enabled = true;
			}
			parent.clearSubRenderers(false, control);
			control.head.clearSuperRenderers(detailLevel, x, y, z, control);
		}

		public float getSize() {
			return size;
		}

		private void alignEdge(VoxelUpdateInfo info, byte x, byte y, byte z) {
			if (info.renderers[x, y, z] == null || (x + y + z > 3 && info.renderers[x, y, z].size == size)) {
				lock (control) {
					VoxelUpdateInfo newInfo = new VoxelUpdateInfo(info.size, info.blocks[1, 1, 1], info.control);
					newInfo.setFromSister(info, x, y, z);
					alignOtherEdge(newInfo, x, y, z);
				}
				return;
			}
			lock (control) {
				info.renderers[x, y, z].removeEdge(info, (byte)(2 - x), (byte)(2 - y), (byte)(2 - z));
			}

			Vector3[] newVerts = VERTS;
			LinkedList<int> myIndices = new LinkedList<int>();
			LinkedList<Vector3[]> otherVerts = new LinkedList<Vector3[]>();

			Vector3[] newNorms = NORMS;

			lock (control) {
				if (x != 1) {
					if (xDim < VERTEX_DIMENSION && x == 2) return;
					int otherXInd = 1 + (VERTEX_DIMENSION - 3) * (1 - x / 2);
					int myXInd = (VERTEX_DIMENSION - 1) * (x / 2);
					for (int yi = 1 - yExtend; yi < yDim; ++yi) {
						for (int zi = 1 - zExtend; zi < zDim; ++zi) {
							addDualVertices(otherVerts, info.renderers[x, y, z], otherXInd, yi, zi, 0);
							myIndices.AddFirst(getY(myXInd, yi, zi));
							myIndices.AddFirst(getZ(myXInd, yi, zi));
						}
					}
					addDualVertices(otherVerts, info.renderers[x, y + 1, z + 1], otherXInd, 0, 0, 0);
					addDualVertices(otherVerts, info.renderers[x, y + 1, z - 1], otherXInd, 0, VERTEX_DIMENSION - 1, 0);
					addDualVertices(otherVerts, info.renderers[x, y - 1, z + 1], otherXInd, VERTEX_DIMENSION - 1, 0, 0);
					addDualVertices(otherVerts, info.renderers[x, y - 1, z - 1], otherXInd, VERTEX_DIMENSION - 1, VERTEX_DIMENSION - 1, 0);

					for (int i = 0; i < VERTEX_DIMENSION; ++i) {
						addDualVertices(otherVerts, info.renderers[x, y, z + 1], otherXInd, i, 0, 0);
						addDualVertices(otherVerts, info.renderers[x, y, z - 1], otherXInd, i, VERTEX_DIMENSION - 1, 0);
						addDualVertices(otherVerts, info.renderers[x, y + 1, z], otherXInd, 0, i, 0);
						addDualVertices(otherVerts, info.renderers[x, y - 1, z], otherXInd, VERTEX_DIMENSION - 1, i, 0);
					}
				} else if (y != 1) {
					if (yDim < VERTEX_DIMENSION && y == 2) return;
					int otherYInd = 1 + (VERTEX_DIMENSION - 3) * (1 - y / 2);
					int myYInd = (VERTEX_DIMENSION - 1) * (y / 2);
					for (int xi = 1 - xExtend; xi < xDim; ++xi) {
						for (int zi = 1 - zExtend; zi < zDim; ++zi) {
							addDualVertices(otherVerts, info.renderers[x, y, z], xi, otherYInd, zi, 1);
							myIndices.AddFirst(getX(xi, myYInd, zi));
							myIndices.AddFirst(getZ(xi, myYInd, zi));
						}
					}
					addDualVertices(otherVerts, info.renderers[x + 1, y, z + 1], 0, otherYInd, 0, 1);
					addDualVertices(otherVerts, info.renderers[x + 1, y, z - 1], 0, otherYInd, VERTEX_DIMENSION - 1, 1);
					addDualVertices(otherVerts, info.renderers[x - 1, y, z + 1], VERTEX_DIMENSION - 1, otherYInd, 0, 1);
					addDualVertices(otherVerts, info.renderers[x - 1, y, z - 1], VERTEX_DIMENSION - 1, otherYInd, VERTEX_DIMENSION - 1, 1);

					for (int i = 0; i < VERTEX_DIMENSION; ++i) {
						addDualVertices(otherVerts, info.renderers[x, y, z + 1], i, otherYInd, 0, 1);
						addDualVertices(otherVerts, info.renderers[x, y, z - 1], i, otherYInd, VERTEX_DIMENSION - 1, 1);
						addDualVertices(otherVerts, info.renderers[x + 1, y, z], 0, otherYInd, i, 1);
						addDualVertices(otherVerts, info.renderers[x - 1, y, z], VERTEX_DIMENSION - 1, otherYInd, i, 1);
					}
				} else if (z != 1) {
					if (zDim < VERTEX_DIMENSION && z == 2) return;
					int otherZInd = 1 + (VERTEX_DIMENSION - 3) * (1 - z / 2);
					int myZInd = (VERTEX_DIMENSION - 1) * (z / 2);
					for (int xi = 1 - xExtend; xi < xDim; ++xi) {
						for (int yi = 1 - yExtend; yi < yDim; ++yi) {
							addDualVertices(otherVerts, info.renderers[x, y, z], xi, yi, otherZInd, 2);
							myIndices.AddFirst(getX(xi, yi, myZInd));
							myIndices.AddFirst(getY(xi, yi, myZInd));
						}
					}
					addDualVertices(otherVerts, info.renderers[x + 1, y + 1, z], 0, 0, otherZInd, 2);
					addDualVertices(otherVerts, info.renderers[x + 1, y - 1, z], 0, VERTEX_DIMENSION - 1, otherZInd, 2);
					addDualVertices(otherVerts, info.renderers[x - 1, y + 1, z], VERTEX_DIMENSION - 1, 0, otherZInd, 2);
					addDualVertices(otherVerts, info.renderers[x - 1, y - 1, z], VERTEX_DIMENSION - 1, VERTEX_DIMENSION - 1, otherZInd, 2);

					for (int i = 0; i < VERTEX_DIMENSION; ++i) {
						addDualVertices(otherVerts, info.renderers[x, y + 1, z], i, 0, otherZInd, 2);
						addDualVertices(otherVerts, info.renderers[x, y - 1, z], i, VERTEX_DIMENSION - 1, otherZInd, 2);
						addDualVertices(otherVerts, info.renderers[x + 1, y, z], 0, i, otherZInd, 2);
						addDualVertices(otherVerts, info.renderers[x - 1, y, z], VERTEX_DIMENSION - 1, i, otherZInd, 2);
					}
				}
			}

			lock (control) {
				foreach (int myIndex in myIndices) {
					if (vertices.ContainsKey(myIndex)) {
						Vector3[] vertex = getClosestVertex(newVerts[(int)vertices[myIndex]], otherVerts);
						if (vertex == null || (newVerts[(int)vertices[myIndex]] -vertex[0]).sqrMagnitude > Mathf.Pow(size /4, 2))
							continue;
						newVerts[(int)vertices[myIndex]] = vertex[0];
						newNorms[(int)vertices[myIndex]] = vertex[1];
					}
				}
			}

			VERTS = newVerts;
			NORMS = newNorms;
		}

		public void addEdge(VoxelUpdateInfo info, byte x, byte y, byte z) {
			if (vertices == null) return;
			bool recalculate = false;
			Voxel[, ,] voxels = new Voxel[VERTEX_DIMENSION, VERTEX_DIMENSION, VERTEX_DIMENSION];
			if (x == 0/* && xExtend == 0*/) {
				recalculate = true;
				xExtend = 1;
				for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						voxels[0, yi, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - xExtend, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION - 1 + zi).toVoxel();
						voxels[1, yi, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION - 1 + zi).toVoxel();
					}
				}
			} else if (x == 2/* && xDim < VERTEX_DIMENSION*/) {
				recalculate = true;
				xDim = VERTEX_DIMENSION;
				for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						voxels[VOXEL_DIMENSION + 1, yi, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION * 2, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION - 1 + zi).toVoxel();
						voxels[VOXEL_DIMENSION, yi, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION * 2 - 1, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION - 1 + zi).toVoxel();
					}
				}
			} else if (y == 0/* && yExtend == 0*/) {
				recalculate = true;
				yExtend = 1;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						voxels[xi, 0, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION - yExtend, VOXEL_DIMENSION - 1 + zi).toVoxel();
						voxels[xi, 1, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION, VOXEL_DIMENSION - 1 + zi).toVoxel();
					}
				}
			} else if (y == 2/* && yDim < VERTEX_DIMENSION*/) {
				recalculate = true;
				yDim = VERTEX_DIMENSION;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						voxels[xi, VOXEL_DIMENSION + 1, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION * 2, VOXEL_DIMENSION - 1 + zi).toVoxel();
						voxels[xi, VOXEL_DIMENSION, zi] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION * 2 - 1, VOXEL_DIMENSION - 1 + zi).toVoxel();
					}
				}
			} else if (z == 0/* && zExtend == 0*/) {
				recalculate = true;
				zExtend = 1;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
						voxels[xi, yi, 0] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION - zExtend).toVoxel();
						voxels[xi, yi, 1] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION).toVoxel();
					}
				}
			} else if (z == 2/* && zDim < VERTEX_DIMENSION*/) {
				recalculate = true;
				zDim = VERTEX_DIMENSION;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
						voxels[xi, yi, VOXEL_DIMENSION + 1] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION * 2).toVoxel();
						voxels[xi, yi, VOXEL_DIMENSION] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + xi, VOXEL_DIMENSION - 1 + yi, VOXEL_DIMENSION * 2 - 1).toVoxel();
					}
				}
			}

			if (recalculate) {


				Queue<int[]> triangleSet = new Queue<int[]>();
				MarchingCubesV2.setup(info.size / VOXEL_DIMENSION, control.isoLevel, ref vertices, ref vertexMaterials, ref voxels, position - new Vector3(0.5f, 0.5f, 0.5f) * size / VOXEL_DIMENSION, VERTS);

				byte xStart = (byte)(1 - xExtend + (VOXEL_DIMENSION + xExtend - 1) * (x / 2));
				byte xEnd = (byte)(2 + (xDim - 2) * ((x + 1) / 2));
				byte yStart = (byte)(1 - yExtend + (VOXEL_DIMENSION + yExtend - 1) * (y / 2));
				byte yEnd = (byte)(2 + (yDim - 2) * ((y + 1) / 2));
				byte zStart = (byte)(1 - zExtend + (VOXEL_DIMENSION + zExtend - 1) * (z / 2));
				byte zEnd = (byte)(2 + (zDim - 2) * ((z + 1) / 2));

				for (byte xi = xStart, x1 = (byte)(xi + 1); x1 < xEnd; xi = x1++) {
					for (byte yi = yStart, y1 = (byte)(yi + 1); y1 < yEnd; yi = y1++) {
						for (byte zi = zStart, z1 = (byte)(zi + 1); z1 < zEnd; zi = z1++) {
							int[] tris = MarchingCubesV2.lookupTriangles(xi, yi, zi, x1, y1, z1);
							if (tris == null) continue;
							triangleSet.Enqueue(tris);
						}
					}
				}

				if (vertices.Count < 1) {
					return;
				}


				List<int> newTriangles = new List<int>(TRIS);
				List<Vector3> newVertices = new List<Vector3>(VERTS);
				List<Vector3> newNorms = new List<Vector3>(NORMS);
				int tri = 0;
				while (triangleSet.Count > 0) {
					int[] triangleList = triangleSet.Dequeue();
					for (int i = 0; i < triangleList.Length; ++i) {
						if (vertices[triangleList[i]].GetType() == typeof(Vector3)) {
							newVertices.Add((Vector3)vertices[triangleList[i]]);
							newNorms.Add(Vector3.zero);
							vertices[triangleList[i]] = newVertices.Count - 1;
						}
						newTriangles.Add((int)vertices[triangleList[i]]);
					}
					tri += triangleList.Length;
				}

				Vector3[] finalNorms = new Vector3[newNorms.Count];
				Array.Copy(NORMS, finalNorms, NORMS.Length);
				int oldNormCount = NORMS.Length;

				VERTS = newVertices.ToArray();
				TRIS = newTriangles.ToArray();
				calcNorms();
				Array.Copy(NORMS, oldNormCount, finalNorms, oldNormCount, finalNorms.Length - oldNormCount);
				NORMS = finalNorms;
			}

			alignEdge(info, x, y, z);
			control.enqueueMeshApply(new ApplyMeshJob(this, info.detailLevel, info.x, info.y, info.z));
		}


		public void removeEdge(VoxelUpdateInfo info, byte x, byte y, byte z) {
			if (vertices == null) return;
			bool recalculate = false;
			if (x == 0 && xExtend == 1) {
				recalculate = true;
				xExtend = 0;
				for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						vertices.Remove(getX(0, yi, zi));
						vertices.Remove(getY(0, yi, zi));
						vertices.Remove(getZ(0, yi, zi));
					}
				}
			} else if (x == 2 && xDim >= VERTEX_DIMENSION) {
				recalculate = true;
				xDim = VERTEX_DIMENSION - 1;
				for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						vertices.Remove(getX(xDim - 1, yi, zi));
						vertices.Remove(getY(xDim, yi, zi));
						vertices.Remove(getZ(xDim, yi, zi));
					}
				}
			} else if (y == 0 && yExtend == 1) {
				recalculate = true;
				yExtend = 0;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						vertices.Remove(getX(xi, 0, zi));
						vertices.Remove(getY(xi, 0, zi));
						vertices.Remove(getZ(xi, 0, zi));
					}
				}
			} else if (y == 2 && yDim >= VERTEX_DIMENSION) {
				recalculate = true;
				yDim = VERTEX_DIMENSION - 1;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte zi = (byte)(1 - zExtend); zi < zDim; ++zi) {
						vertices.Remove(getX(xi, yDim, zi));
						vertices.Remove(getY(xi, yDim - 1, zi));
						vertices.Remove(getZ(xi, yDim, zi));
					}
				}
			} else if (z == 0 && zExtend == 1) {
				recalculate = true;
				zExtend = 0;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
						vertices.Remove(getX(xi, yi, 0));
						vertices.Remove(getY(xi, yi, 0));
						vertices.Remove(getZ(xi, yi, 0));
					}
				}
			} else if (z == 2 && zDim >= VERTEX_DIMENSION) {
				recalculate = true;
				zDim = VERTEX_DIMENSION - 1;
				for (byte xi = (byte)(1 - xExtend); xi < xDim; ++xi) {
					for (byte yi = (byte)(1 - yExtend); yi < yDim; ++yi) {
						vertices.Remove(getX(xi, yi, zDim));
						vertices.Remove(getY(xi, yi, zDim));
						vertices.Remove(getZ(xi, yi, zDim - 1));
					}
				}
			}
			if (recalculate) {
				List<KeyValuePair<int, object>> vertexList = new List<KeyValuePair<int, object>>(vertices);
				int[] oldTris = TRIS;
				Vector3[] oldVerts = VERTS;
				Vector3[] oldNorms = NORMS;
				List<int> newTris = new List<int>(TRIS.Length);
				Vector3[] newVerts = new Vector3[vertexList.Count];
				Vector3[] newNorms = new Vector3[newVerts.Length];

				object[] oldReverseIndices = new object[oldVerts.Length];


				int count = 0;
				foreach (KeyValuePair<int, object> pair in vertexList) {
					int oldIndex = (int)pair.Value;
					vertices[pair.Key] = count;
					newVerts[count] = oldVerts[oldIndex];
					newNorms[count] = oldNorms[oldIndex];
					oldReverseIndices[oldIndex] = pair.Key;
					++count;
				}

				int[] triangle = new int[3];
				for (int i = 0; i < oldTris.Length; i += 3) {
					bool old = false;
					for (int j = 0; j < 3; ++j) {
						object newIndex = oldReverseIndices[oldTris[i + j]];
						if (newIndex == null) {
							old = true;
							break;
						}
						triangle[j] = (int)vertices[(int)newIndex];
					}
					if (old) continue;
					newTris.AddRange(triangle);
				}

				VERTS = newVerts;
				NORMS = newNorms;
				TRIS = newTris.ToArray();
				control.enqueueMeshApply(new ApplyMeshJob(this, info.detailLevel, info.x, info.y, info.z));
			}
		}

		private static void addDualVertices(LinkedList<Vector3[]> otherVerts, VoxelRenderer rend, int x, int y, int z, byte xyz) {
			Vector3[] otherVert1;
			Vector3[] otherVert2;
			switch (xyz) {
				case 0:
					otherVert1 = getVertex(rend, getY(x, y, z));
					otherVert2 = getVertex(rend, getZ(x, y, z));
					break;
				case 1:
					otherVert1 = getVertex(rend, getX(x, y, z));
					otherVert2 = getVertex(rend, getZ(x, y, z));
					break;
				case 2:
					otherVert1 = getVertex(rend, getX(x, y, z));
					otherVert2 = getVertex(rend, getY(x, y, z));
					break;
				default:
					return;
			}
			if (otherVert1 != null) otherVerts.AddFirst(otherVert1);
			if (otherVert2 != null) otherVerts.AddFirst(otherVert2);
		}

		private static Vector3[] getVertex(VoxelRenderer rend, int hashIndex) {
			if (rend == null || rend.vertices == null) return null;
			if (!rend.vertices.ContainsKey(hashIndex)) return null;
			object index = rend.vertices[hashIndex];
			return new Vector3[] {
				rend.VERTS[(int)index],
				rend.NORMS[(int)index]
			};
		}

		private void alignOtherEdge(VoxelUpdateInfo info, byte x, byte y, byte z) {

			VoxelRenderer other = info.renderers[1, 1, 1];
			if (other == null) {
				if (info.blocks[1, 1, 1].GetType() == typeof(VoxelBlock)) {

					byte xStart = (byte)((VoxelBlock.CHILD_DIMENSION - 1) * (2 - x) / 2);
					byte xEnd = (byte)(1 + (VoxelBlock.CHILD_DIMENSION - 1) * (1 - x / 2));
					byte yStart = (byte)((VoxelBlock.CHILD_DIMENSION - 1) * (2 - y) / 2);
					byte yEnd = (byte)(1 + (VoxelBlock.CHILD_DIMENSION - 1) * (1 - y / 2));
					byte zStart = (byte)((VoxelBlock.CHILD_DIMENSION - 1) * (2 - z) / 2);
					byte zEnd = (byte)(1 + (VoxelBlock.CHILD_DIMENSION - 1) * (1 - z / 2));

					for (byte xi = xStart; xi < xEnd; ++xi) {
						for (byte yi = yStart; yi < yEnd; ++yi) {
							for (byte zi = zStart; zi < zEnd; ++zi) {
								alignOtherEdge(new VoxelUpdateInfo(info, xi, yi, zi), x, y, z);
							}
						}
					}
				}
				return;
			}
			other.addEdge(info, (byte)(2 - x), (byte)(2 - y), (byte)(2 - z));
		}

		private Vector3[] getClosestVertex(Vector3 position, LinkedList<Vector3[]> otherVertices) {
			Vector3[] closest = null;
			float closestDis = float.MaxValue;
			foreach (Vector3[] otherVertex in otherVertices) {
				float newDis = (position - otherVertex[0]).sqrMagnitude;
				if (closestDis > newDis) {
					closest = otherVertex;
					closestDis = newDis;
				}
			}
			return closest;
		}

		public static int getX(int x, int y, int z) {
			return (y * VERTEX_DIMENSION + z) * VERTEX_DIMENSION + x;
		}

		public static int getY(int x, int y, int z) {
			return ((VERTEX_DIMENSION + x) * VERTEX_DIMENSION + z) * VERTEX_DIMENSION + y;
		}

		public static int getZ(int x, int y, int z) {
			return ((VERTEX_DIMENSION * 2 + x) * VERTEX_DIMENSION + y) * VERTEX_DIMENSION + z;
		}

		//private static int getX(int index, int dimension) {
		//	return (y * VERTEX_DIMENSION + z) * VERTEX_DIMENSION + x;
		//}

		//private static int getY(int index, int dimension) {
		//	return ((VERTEX_DIMENSION + x) * VERTEX_DIMENSION + z) * VERTEX_DIMENSION + y;
		//}

		//private static int getZ(int index, int dimension) {
		//	return ((VERTEX_DIMENSION * 2 + x) * VERTEX_DIMENSION + y) * VERTEX_DIMENSION + z;
		//}

		//private static int getDimension(int index) {
		//	return index / (VERTEX_DIMENSION * VERTEX_DIMENSION * VERTEX_DIMENSION);
		//}

		private Voxel[, ,] createVoxelArray(VoxelUpdateInfo info) {

			setDimensions(info);
			Voxel[, ,] voxels = new Voxel[VERTEX_DIMENSION, VERTEX_DIMENSION, VERTEX_DIMENSION];

			for (byte y = (byte)(1 - yExtend); y < yDim; ++y) {
				for (byte z = (byte)(1 - zExtend); z < zDim; ++z) {
					voxels[1 - xExtend, y, z] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - xExtend, VOXEL_DIMENSION - 1 + y, VOXEL_DIMENSION - 1 + z).toVoxel();
				}
			}
			for (byte x = (byte)(2 - xExtend); x < xDim; ++x) {
				for (byte z = (byte)(1 - zExtend); z < zDim; ++z) {
					voxels[x, 1 - yExtend, z] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + x, VOXEL_DIMENSION - yExtend, VOXEL_DIMENSION - 1 + z).toVoxel();
				}
			}
			for (byte x = (byte)(2 - xExtend); x < xDim; ++x) {
				for (byte y = (byte)(2 - yExtend); y < yDim; ++y) {
					voxels[x, y, 1 - zExtend] = info.getSub(VOXEL_COUNT_POWER, VOXEL_DIMENSION - 1 + x, VOXEL_DIMENSION - 1 + y, VOXEL_DIMENSION - zExtend).toVoxel();
				}
			}

			return voxels;
		}

		private void setDimensions(VoxelUpdateInfo info) {
			if (info.renderers[0, 1, 1] == null)
				xExtend = 0;
			else
				xExtend = 1;
			if (info.renderers[1, 0, 1] == null)
				yExtend = 0;
			else
				yExtend = 1;
			if (info.renderers[1, 1, 0] == null)
				zExtend = 0;
			else
				zExtend = 1;
			xDim = (byte)(VOXEL_DIMENSION + 1);
			yDim = (byte)(VOXEL_DIMENSION + 1);
			zDim = (byte)(VOXEL_DIMENSION + 1);
			if (info.renderers[2, 1, 1] != null && info.renderers[2, 1, 1].size > size * 1.1f)
				++xDim;
			if (info.renderers[1, 2, 1] != null && info.renderers[1, 2, 1].size > size * 1.1f)
				++yDim;
			if (info.renderers[1, 1, 2] != null && info.renderers[1, 1, 2].size > size * 1.1f)
				++zDim;
		}

		private void calcNorms() {
			Vector3[] norms = new Vector3[VERTS.Length];
			for(int i=0; i<norms.Length; ++i) {
				norms[i] = Vector3.zero;
			}
			for (int i = 0; i < TRIS.Length;) {
				int A = TRIS[i++];
				int B = TRIS[i++];
				int C = TRIS[i++];
				Vector3 surfNorm = Vector3.Cross(VERTS[B] - VERTS[A], VERTS[C] - VERTS[A]);
				surfNorm = surfNorm * (1 - NORMAL_SMOOTHNESS + NORMAL_SMOOTHNESS / Mathf.Max(surfNorm.sqrMagnitude, 0.00000001f));
				norms[A] += surfNorm;
				norms[B] += surfNorm;
				norms[C] += surfNorm;
			}
			for (int i = 0; i < norms.Length; ++i) {
				norms[i].Normalize();
			}
			NORMS = norms;
		}

		public VoxelControlV2 getControl() {
			return control;
		}

		private void removePolyCount() {
			if (obs != null) {
				foreach (GameObject ob in obs) {
					triangleCount -= ob.GetComponent<MeshFilter>().sharedMesh.triangles.Length / 3;
					vertexCount -= ob.GetComponent<MeshFilter>().sharedMesh.vertexCount;
				}
			}
		}

		private void addPolyCount() {
			if (obs != null) {
				foreach (GameObject ob in obs) {
					triangleCount += ob.GetComponent<MeshFilter>().sharedMesh.triangles.Length / 3;
					vertexCount += ob.GetComponent<MeshFilter>().sharedMesh.vertexCount;
				}
			}
		}
	}

}