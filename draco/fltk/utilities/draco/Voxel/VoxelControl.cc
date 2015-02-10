using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class VoxelControl : MonoBehaviour {

	public float voxelSize = 0.25f;
	public int terrainXSize;
	public int terrainYSize;
	public int terrainZSize;
	public int chunkSize;
	public Material voxelMat;
	public float maxChange;
	public float isoLevel = 0.2f;
	public GameObject trees;
	public float treeDensity = 0.1f;
	public float treeSlopeTolerance = 5;
	public Texture2D grassTexture;
	

	// generation performance stats
	private float lookuptime=0, converttime=0, meshtime=0, attachtime=0;
	private int treeCount=0, voxelVertexCount=0, voxelTriangleCount=0;
	private int xGen = 0, yGen = 0, zGen = 0;
	private int generatingStage = 0;

	private VoxelChunk[, , ] chunks;
	//private TerrainData terrainData;

	void Start() {
		float starttime = Time.realtimeSinceStartup;

		// Pass 1: create and initialize the chunks
		chunks = new VoxelChunk[terrainXSize, terrainYSize, terrainZSize];
		for (int x = 0; x < terrainXSize; ++x) {
			for (int y = 0; y < terrainYSize; ++y) {
				for (int z = 0; z < terrainZSize; ++z) {
					chunks[x, y, z] = new GameObject("VoxelChunk").AddComponent<VoxelChunk>();
					chunks[x, y, z].initialize(this, chunkSize + 1, x, y, z);
					chunks[x, y, z].transform.localPosition = new Vector3(x * chunkSize * voxelSize, y * chunkSize * voxelSize, z * chunkSize * voxelSize);
				}
			}
		}

		// Pass 2: set the voxels
		genData(0);
		float endtime = Time.realtimeSinceStartup;
		print("total terrain generation time: " +(endtime -starttime));
		xGen = yGen = zGen = 0;

		// Pass 3: generate the meshes
		if (generatingStage == 0) {
			//float starttime2 = Time.realtimeSinceStartup;
			for (; xGen < terrainXSize; ++xGen) {
				for (; zGen < terrainZSize; ) {
					for (; yGen < terrainYSize; ++yGen) {
						chunks[xGen, yGen, zGen].genTriangles();
					}
					yGen = 0;
					++zGen;
					//return;
				}
				zGen = 0;
			}
			xGen = yGen = zGen = 0;
			generatingStage = 1;
		}

		if (generatingStage == 1) {
			for (; xGen < terrainXSize;) {
				for (; zGen < terrainZSize; ++zGen) {
					for (; yGen < terrainYSize; ++yGen) {
						chunks[xGen, yGen, zGen].genMesh();
					}
					yGen = 0;
				}
				zGen = 0;
				++xGen;
				//return;
			}
			generatingStage = 2;
			float endtime2 = Time.realtimeSinceStartup;
			print("total chunk setup time:        " + (endtime2 - starttime));

			print("average chunk lookup time:  " + (lookuptime) / terrainXSize / terrainYSize / terrainZSize);
			print("average chunk convert time: " + (converttime) / terrainXSize / terrainYSize / terrainZSize);
			print("average chunk mesh time:    " + (meshtime) / terrainXSize / terrainYSize / terrainZSize);
			print("average chunk attach time:  " + (attachtime) / terrainXSize / terrainYSize / terrainZSize);
			print("total tree count:           " + treeCount);
			print("total voxel vertex count:   " + voxelVertexCount);
			print("total voxel triangle count:   " + voxelTriangleCount);
		}
	}

	public float subtractSphere(Vector3 worldLocation, float radius) {

		Vector3 corner = (transform.InverseTransformPoint(worldLocation) -new Vector3(radius, radius, radius)) /voxelSize;
		//print(corner);
		int xCorner1 = (int)corner.x;
		int yCorner1 = (int)corner.y;
		int zCorner1 = (int)corner.z;
		corner = corner +new Vector3(radius, radius, radius) /voxelSize *2;
		//print(corner);
		int xCorner2 = (int)(corner.x +0.5f);
		int yCorner2 = (int)(corner.y +0.5f);
		int zCorner2 = (int)(corner.z +0.5f);

		float minDis = (radius - voxelSize / 2);
		//minDis *= minDis;
		float maxDis = (radius + voxelSize / 2);
		//maxDis *= maxDis;
		float totalMaterial = 0;

		for (int x = xCorner1; x < xCorner2; ++x) {
			int xChunk = x /chunkSize;
			int xIndex = x -xChunk *chunkSize;
			for (int y = yCorner1; y < yCorner2; ++y) {
				int yChunk = y /chunkSize;
				int yIndex = y -yChunk *chunkSize;
				for (int z = zCorner1; z < zCorner2; ++z) {
					int zChunk = z /chunkSize;
					int zIndex = z -zChunk *chunkSize;
					float dis = (worldLocation -transform.TransformPoint(new Vector3(x +0.5f, y +0.5f, z +0.5f) *voxelSize)).magnitude;
					if (dis > maxDis) continue;
					float newvalue;
					if (dis < minDis) {
						newvalue = 0;
					} else {
						newvalue = (dis - minDis) / (maxDis - minDis);
						if (newvalue >= chunks[xChunk, yChunk, zChunk].voxels[xIndex, yIndex, zIndex])
							continue;
					}
					totalMaterial += chunks[xChunk, yChunk, zChunk].voxels[xIndex, yIndex, zIndex] - newvalue;
					chunks[xChunk, yChunk, zChunk].voxels[xIndex, yIndex, zIndex] = newvalue;

					// handle edges
					if (xIndex == 0 && xChunk > 0) {
						chunks[xChunk - 1, yChunk, zChunk].voxels[chunkSize, yIndex, zIndex] = newvalue;
						if (yIndex == 0 && yChunk > 0) {
							chunks[xChunk - 1, yChunk - 1, zChunk].voxels[chunkSize, chunkSize, zIndex] = newvalue;
							if (zIndex == 0 && zChunk > 0) {
								chunks[xChunk - 1, yChunk - 1, zChunk -1].voxels[chunkSize, chunkSize, chunkSize] = newvalue;
							}
						}
					}
					if (yIndex == 0 && yChunk > 0) {
						chunks[xChunk, yChunk - 1, zChunk].voxels[xIndex, chunkSize, zIndex] = newvalue;
						if (zIndex == 0 && zChunk > 0) {
							chunks[xChunk, yChunk - 1, zChunk - 1].voxels[xIndex, chunkSize, chunkSize] = newvalue;
						}
					}
					if (zIndex == 0 && zChunk > 0) {
						chunks[xChunk, yChunk, zChunk -1].voxels[xIndex, yIndex, chunkSize] = newvalue;
						if (xIndex == 0 && xChunk > 0) {
							chunks[xChunk - 1, yChunk, zChunk - 1].voxels[chunkSize, yIndex, chunkSize] = newvalue;
						}
					}
				}
			}
		}

		for (int x = (xCorner1 -1) /chunkSize; x <= xCorner2 /chunkSize; ++x) {
			for (int y = (yCorner1 -1) / chunkSize; y <= yCorner2 / chunkSize; ++y) {
				for (int z = (zCorner1 -1) / chunkSize; z <= zCorner2 / chunkSize; ++z) {
					//print(x +", " +y +", " +z);
					chunks[x, y, z].genTriangles();
					chunks[x, y, z].genMesh();
				}
			}
		}

		return totalMaterial;
	}

	public VoxelChunk[, , ] getChunks() {
		return chunks;
	}

	// this functions sets the values of the voxels, doing all of the procedural generation work
	// currently it just uses a "height map" system.  This is fine for initial generation, but
	// then more passes need to be done for cliffs, caves, streams, etc.
	private void genData(int seed) {
		Random.seed = seed;
		float acceleration = 0;
		float height = terrainYSize * chunkSize *0.8f;
		float[, ] heightMap = new float[terrainXSize * chunkSize, terrainZSize *chunkSize];
		float[, ] accelMap = new float[terrainXSize * chunkSize, terrainZSize *chunkSize];
		for (int x = 0; x < terrainXSize * chunkSize; ++x) {
			int xChunk = x / chunkSize;
			int xInner = x - xChunk * chunkSize;
			bool setX = (xInner == 0 && xChunk > 0);
			for (int z = 0; z < terrainZSize * chunkSize; ++z) {
				int zChunk = z / chunkSize;
				int zInner = z - zChunk * chunkSize;
				bool setZ = (zInner == 0 && zChunk > 0);

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
				float edgeDistance = Mathf.Max(Mathf.Abs(terrainXSize * chunkSize / 2 - x -10), Mathf.Abs(terrainZSize * chunkSize / 2 - z -10));
				float edgeDistancePercent = 1 - edgeDistance / (Mathf.Min(terrainXSize, terrainZSize) * chunkSize / 2);
				float percent;
				if (edgeDistancePercent < 0.2)
					percent = height / (terrainYSize * chunkSize * 0.8f) - 0.4f;
				else
					percent = height / (terrainYSize * chunkSize * 0.6f);
				float roughness = maxChange + 0.2f * (1 - edgeDistancePercent);
				acceleration += Random.Range(-roughness * percent, roughness * (1 - percent));
				acceleration = Mathf.Min(Mathf.Max(acceleration, -roughness * 4), roughness * 4);
				height = Mathf.Min(Mathf.Max(height + acceleration, 0), terrainYSize * chunkSize);
				heightMap[x, z] = height;
				accelMap[x, z] = acceleration;

				// set the voxels to that height
				bool setCorner = (setX && setZ);
				for (int y = 0; y < terrainYSize * chunkSize; ++y) {
					int yChunk = y / chunkSize;
					int yInner = y - yChunk * chunkSize;
					float val;
					if (y >= height)
						break;
					else if (y >= height - 1)
						val = height - y;
					//else if (y >= height - 2)
					//	val = 1 -(1 -(height - y))/2;
					else
						val = 1;
					chunks[xChunk, yChunk, zChunk].voxels[xInner, yInner, zInner] = val;
					bool setY = (yInner == 0 && yChunk > 0);
					if (setX) {
						chunks[xChunk - 1, yChunk, zChunk].voxels[chunkSize, yInner, zInner] = val;
						if (setY)
							chunks[xChunk - 1, yChunk - 1, zChunk].voxels[chunkSize, chunkSize, zInner] = val;
					}
					if (setZ) {
						chunks[xChunk, yChunk, zChunk - 1].voxels[xInner, yInner, chunkSize] = val;
						if (setY)
							chunks[xChunk, yChunk - 1, zChunk - 1].voxels[xInner, chunkSize, chunkSize] = val;
					}
					if (setCorner) {
						chunks[xChunk - 1, yChunk, zChunk - 1].voxels[chunkSize, yInner, chunkSize] = val;
						if (setY)
							chunks[xChunk - 1, yChunk - 1, zChunk - 1].voxels[chunkSize, chunkSize, chunkSize] = val;
					}
					if (setY)
						chunks[xChunk, yChunk - 1, zChunk].voxels[xInner, chunkSize, zInner] = val;
				}
			}
		}

		// generate trees
		for (int x = 0; x < terrainXSize * chunkSize; ++x) {
			for (int z = 0; z < terrainZSize * chunkSize; ++z) {
				if (Random.Range(Mathf.Abs(accelMap[x, z]) /treeSlopeTolerance, 1) < treeDensity) {
					GameObject tree = (GameObject) GameObject.Instantiate(trees);
					tree.transform.parent = transform;
					tree.transform.localPosition = new Vector3(x * voxelSize, heightMap[x, z] *voxelSize -1.5f, z * voxelSize);
					++treeCount;
				}
			}
		}

		// generate grass  FAILED?
		//DetailPrototype[] detailVeggies = new DetailPrototype[1];
		//detailVeggies[0] = new DetailPrototype();
		//detailVeggies[0].bendFactor = 1;
		//detailVeggies[0].dryColor = Color.green;
		//detailVeggies[0].healthyColor = Color.green;
		//detailVeggies[0].prototypeTexture = grassTexture;
		//detailVeggies[0].renderMode = DetailRenderMode.Grass;
		//detailVeggies[0].maxWidth = 1;
		//detailVeggies[0].minWidth = 1;
		//detailVeggies[0].maxHeight = 2;
		//detailVeggies[0].minHeight = 2;

		//terrainData = new TerrainData();
		//terrainData.detailPrototypes = detailVeggies;
		//terrainData.SetDetailResolution(10000, 16);
		//terrainData.size = new Vector3(100, 100, 100);
		//int[,] map = new int[33,33];
		//for(int i=0; i<33; ++i)
		//	for(int j=0; j<33; ++j)
		//		map[i, j] = 50;
		//float[,] heights = new float[33,33];
		//for(int i=0; i<33; ++i)
		//	for(int j=0; j<33; ++j)
		//		heights[i, j] = 0;
		//terrainData.SetHeights(0, 0, heights);
		//terrainData.SetDetailLayer(0, 0, 0, map);
	}

	public void addToLookuptime(float time) {
		lookuptime += time;
	}

	public void addToConverttime(float time) {
		converttime += time;
	}

	public void addToMeshtime(float time) {
		meshtime += time;
	}

	public void addToAttachtime(float time) {
		attachtime += time;
	}

	public void addToVoxelVertexCount(int count) {
		voxelVertexCount += count;
	}

	public void addToVoxelTriangleCount(int count) {
		voxelTriangleCount += count;
	}
}
