using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public class VoxelChunk : MonoBehaviour {

	public float[,,] voxels;
	public VoxelControl control;

	private Mesh voxelMesh;
	//private Vector3[] vertices;
	private Hashtable vertices;
	private int size;
	private int xIndex, yIndex, zIndex;
	private Mesh mesh;
	private MeshCollider col;
	private MeshFilter filter;
	private MeshRenderer renderer;
	//private int generatedLayer;

	public void initialize(VoxelControl c, int s, int chunkX, int chunkY, int chunkZ) {
		control = c;
		size = s;
		xIndex = chunkX; yIndex = chunkY; zIndex = chunkZ;
		transform.parent = control.transform;
		filter = gameObject.AddComponent<MeshFilter>();
		renderer = gameObject.AddComponent<MeshRenderer>();
		renderer.sharedMaterial = control.voxelMat;
		col = gameObject.AddComponent<MeshCollider>();
		mesh = new Mesh();
		mesh.MarkDynamic();
		filter.sharedMesh = mesh;
		col.sharedMesh = mesh;
		renderer.enabled = false;
		col.enabled = false;

		// generate the voxels
		//vertices = new Vector3[(size - 1) * 3 * size * size];
		voxels = new float[size,size,size];
		for (int x = 0; x < size; ++x) {
			for (int y = 0; y < size; ++y) {
				for (int z = 0; z < size; ++z) {
					voxels[x, y, z] = 0;// createVoxel(chunkX * size + x, chunkY * size + y, chunkZ * size + z);
				}
			}
		}
		//for (int x = 0; x < size; ++x) {
		//	for (int y = 0; y < size; ++y) {
		//		if (chunkZ > 0)
		//			voxels[x][y][0] = control.getChunks()[chunkX][chunkY][chunkZ - 1].voxels[x][y][size - 1];
		//	}
		//	for (int z = 1; z < size; ++z) {
		//		if (chunkY > 0)
		//			voxels[x][0][z] = control.getChunks()[chunkX][chunkY - 1][chunkZ].voxels[x][size - 1][z];
		//	}
		//}
		//for (int y = 0; y < size; ++y) {
		//	for (int z = 1; z < size; ++z) {
		//		if (chunkX > 0)
		//			voxels[0][y][z] = control.getChunks()[chunkX - 1][chunkY][chunkZ].voxels[size - 1][y][z];
		//	}
		//}
		gameObject.AddComponent<MineVoxelEvent>();
	}

	public void genTriangles() {
		mesh.normals = new Vector3[0];
		mesh.uv = new Vector2[0];
		mesh.triangles = new int[0];
		mesh.tangents = new Vector4[0];
		mesh.vertices = new Vector3[0];
		renderer.enabled = false;
		col.enabled = false;


		//float starttime = Time.realtimeSinceStartup;
		Queue<int[]> triangleSet = new Queue<int[]>();
		//Vector3[] vertices = new Vector3[(size - 1) * 3 * size * size];
		vertices = new Hashtable();
		MarchingCubes.setup(size, control.voxelSize, control.isoLevel, ref vertices, ref voxels);
		int totalTris = 0;
		int x1=0;
		for (int x = 0; x < size -1; x=x1) {
			++x1;
			int y1 = 0;
			for (int y = 0; y < size -1; y=y1) {
				++y1;
				int z1=0;
				for (int z = 0; z < size -1; z=z1) {
					++z1;
					if (voxels[x, y, z] < control.isoLevel &&
						voxels[x, y, z1] < control.isoLevel &&
						voxels[x, y1, z] < control.isoLevel &&
						voxels[x, y1, z1] < control.isoLevel &&
						voxels[x1, y, z] < control.isoLevel &&
						voxels[x1, y, z1] < control.isoLevel &&
						voxels[x1, y1, z] < control.isoLevel &&
						voxels[x1, y1, z1] < control.isoLevel)
						continue;
					int[] tris = MarchingCubes.polygonise(x, y, z, x1, y1, z1);
					if (tris == null) continue;
					triangleSet.Enqueue(tris);
					totalTris += tris.Length;
				}
			}
		}
		//float lookuptime = Time.realtimeSinceStartup;

		if (vertices.Count < 1) {
			return;
		}


		int[] triangles = new int[totalTris];
		//Vector2[] uv1 = new Vector2[vertices.Length];
		List<Vector3> finalVertices = new List<Vector3>(vertices.Count);
		int tri = 0;
		while (triangleSet.Count > 0) {
			int[] triangleList = triangleSet.Dequeue();
			for (int i = 0; i < triangleList.Length; ++i) {
				//uv1[triangleList[i]] = new Vector2(vertices[triangleList[i]].x + vertices[triangleList[i]].y, vertices[triangleList[i]].z + vertices[triangleList[i]].y);
				if (vertices[triangleList[i]].GetType() == typeof(Vector3)) {
					finalVertices.Add((Vector3) vertices[triangleList[i]]);
					vertices[triangleList[i]] = finalVertices.Count -1;
				}
				triangles[tri + triangleList.Length - 1 - i] = (int) vertices[triangleList[i]];
			}
			tri += triangleList.Length;
		}
		//float converttime = Time.realtimeSinceStartup;
		mesh.vertices = finalVertices.ToArray();
		mesh.triangles = triangles;
		//mesh.uv = uv1;
		mesh.RecalculateNormals();

		// calculate edge normals... UG!
		Vector3[] norms = mesh.normals;
		Vector3[] otherNorms;
		Vector3 normal;
		VoxelChunk other;
		int myIndex, otherIndex;
		// bottom
		if (yIndex > 0) {
			other = control.getChunks()[xIndex, yIndex - 1, zIndex];
			otherNorms = other.mesh.normals;
			for (int x = 1; x < size; ++x) {
				for (int z = 1; z < size; ++z) {
					if (vertices[((size - 2 + z) * size) * size + x] != null) {
						myIndex = (int) vertices[((size - 2 + z) * size) * size + x];
						otherIndex = (int) other.vertices[((size - 1 + z) * size - 1) * size + x];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
					if (vertices[((x - 1) * size) * size + z] != null) {
						myIndex = (int) vertices[((x - 1) * size) * size + z];
						otherIndex = (int) other.vertices[(x * size - 1) * size + z];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
				}
			}
			control.getChunks()[xIndex, yIndex - 1, zIndex].mesh.normals = otherNorms;
		}
		// back
		if (zIndex > 0) {
			other = control.getChunks()[xIndex, yIndex, zIndex - 1];
			otherNorms = other.mesh.normals;
			for (int x = 1; x < size; ++x) {
				for (int y = 1; y < size; ++y) {
					if (vertices[((size * 2 - 3 + y) * size + x) * size] != null) {
						myIndex = (int) vertices[((size * 2 - 3 + y) * size + x) * size];
						otherIndex = (int) other.vertices[((size * 2 - 3 + y) * size + x + 1) * size - 1];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
					if (vertices[((x - 1) * size + y) * size] != null) {
						myIndex = (int) vertices[((x - 1) * size + y) * size];
						otherIndex = (int) other.vertices[((x - 1) * size + y + 1) * size - 1];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
				}
			}
			control.getChunks()[xIndex, yIndex, zIndex - 1].mesh.normals = otherNorms;
		}
		// side
		if (xIndex > 0) {
			other = control.getChunks()[xIndex - 1, yIndex, zIndex];
			otherNorms = other.mesh.normals;
			for (int z = 1; z < size; ++z) {
				for (int y = 1; y < size; ++y) {
					if (vertices[((size * 2 - 3 + y) * size) * size + z] != null) {
						myIndex = (int) vertices[((size * 2 - 3 + y) * size) * size + z];
						otherIndex = (int) other.vertices[((size * 2 - 2 + y) * size - 1) * size + z];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
					if (vertices[((size + z - 2) * size + y) * size] != null) {
						myIndex = (int) vertices[((size + z - 2) * size + y) * size];
						otherIndex = (int) other.vertices[((size + z - 2) * size + y + 1) * size - 1];
						normal = (norms[myIndex] + otherNorms[otherIndex]) / 2;
						norms[myIndex] = normal;
						otherNorms[otherIndex] = normal;
					}
				}
			}
			control.getChunks()[xIndex - 1, yIndex, zIndex].mesh.normals = otherNorms;
		}
		mesh.normals = norms;

		//float meshtime = Time.realtimeSinceStartup;

		//control.addToLookuptime(lookuptime -starttime);
		//control.addToConverttime(converttime -lookuptime);
		//control.addToMeshtime(meshtime -converttime);
		//control.addToVoxelVertexCount(mesh.vertexCount);
		//control.addToVoxelTriangleCount(mesh.triangles.Length /3);
		//control.addToHashSize(Marshal.SizeOf(vertices));

		//print("lookup time:  " + (lookuptime - starttime));
		//print("convert time: " + (converttime - lookuptime));
		//print("mesh time:    " + (meshtime - converttime));
		//print("attach time:  " + (attachtime - meshtime));
		//print("total time:   " + (attachtime - starttime));
	}

	public void genMesh() {
		if (vertices.Count < 1)
			return;
		//float starttime = Time.realtimeSinceStartup;
		mesh.RecalculateBounds();
		mesh.Optimize();
		renderer.enabled = true;
		col.enabled = true;
		//float attachtime = Time.realtimeSinceStartup;
		//control.addToAttachtime(attachtime - starttime);
	}

	///*
	//	Given a grid cell and an isolevel, calculate the triangular
	//	facets required to represent the isosurface through the cell.
	//	Return the number of triangular facets, the array "triangles"
	//	will be loaded up with the vertices at most 5 triangular facets.
	//	0 will be returned if the grid cell is either totally above
	//	or totally below the isolevel.
	//*/
	//private int[] Polygonise(int x, int y, int z, int x1, int y1, int z1, float isolevel, Hashtable vertices) {
	//	int i,ntriang;
	//	int cubeindex;


	//	/*
	//		Determine the index into the edge table which
	//		tells us which vertices are inside of the surface
	//	*/
	//	cubeindex = 0;
	//	if (voxels[x ][y ][z ] < isolevel) cubeindex |= 1;
	//	if (voxels[x1][y ][z ] < isolevel) cubeindex |= 2;
	//	if (voxels[x1][y ][z1] < isolevel) cubeindex |= 4;
	//	if (voxels[x ][y ][z1] < isolevel) cubeindex |= 8;
	//	if (voxels[x ][y1][z ] < isolevel) cubeindex |= 16;
	//	if (voxels[x1][y1][z ] < isolevel) cubeindex |= 32;
	//	if (voxels[x1][y1][z1] < isolevel) cubeindex |= 64;
	//	if (voxels[x ][y1][z1] < isolevel) cubeindex |= 128;

	//	/* Cube is entirely in/out of the surface */
	//	if (edgeTable[cubeindex] == 0)
	//		return null;

	//	/* Find the vertices where the surface intersects the cube */
	//	if ((edgeTable[cubeindex] & 1) != 0) {
	//		vertlist[0] = (x * size + y) * size + z;
	//		VertexInterp(isolevel, x, y, z, x1, y, z, voxels[x][y][z], voxels[x1][y][z], vertlist[0]);
	//	}
	//	if ((edgeTable[cubeindex] & 2) != 0) {
	//		vertlist[1] = ((size - 1 + z) * size + y) * size + x1;
	//		VertexInterp(isolevel, x1, y, z, x1, y, z1, voxels[x1][y][z], voxels[x1][y][z1], vertlist[1]);
	//	}
	//	if ((edgeTable[cubeindex] & 4) != 0) {
	//		vertlist[2] = (x * size + y) * size + z1;
	//		VertexInterp(isolevel, x1, y, z1, x, y, z1, voxels[x1][y][z1], voxels[x][y][z1], vertlist[2]);
	//	}
	//	if ((edgeTable[cubeindex] & 8) != 0) {
	//		vertlist[3] = ((size - 1 + z) * size + y) * size + x;
	//		VertexInterp(isolevel, x, y, z1, x, y, z, voxels[x][y][z1], voxels[x][y][z], vertlist[3]);
	//	}
	//	if ((edgeTable[cubeindex] & 16) != 0) {
	//		vertlist[4] = (x * size + y1) * size + z;
	//		VertexInterp(isolevel, x, y1, z, x1, y1, z, voxels[x][y1][z], voxels[x1][y1][z], vertlist[4]);
	//	}
	//	if ((edgeTable[cubeindex] & 32) != 0) {
	//		vertlist[5] = ((size - 1 + z) * size + y1) * size + x1;
	//		VertexInterp(isolevel, x1, y1, z, x1, y1, z1, voxels[x1][y1][z], voxels[x1][y1][z1], vertlist[5]);
	//	}
	//	if ((edgeTable[cubeindex] & 64) != 0) {
	//		vertlist[6] = (x * size + y1) * size + z1;
	//		VertexInterp(isolevel, x1, y1, z1, x, y1, z1, voxels[x1][y1][z1], voxels[x][y1][z1], vertlist[6]);
	//	}
	//	if ((edgeTable[cubeindex] & 128) != 0) {
	//		vertlist[7] = ((size - 1 + z) * size + y1) * size + x;
	//		VertexInterp(isolevel, x, y1, z1, x, y1, z, voxels[x][y1][z1], voxels[x][y1][z], vertlist[7]);
	//	}
	//	if ((edgeTable[cubeindex] & 256) != 0) {
	//		vertlist[8] = ((size *2 - 2 + y) * size + x) * size + z;
	//		VertexInterp(isolevel, x, y, z, x, y1, z, voxels[x][y][z], voxels[x][y1][z], vertlist[8]);
	//	}
	//	if ((edgeTable[cubeindex] & 512) != 0) {
	//		vertlist[9] = ((size * 2 - 2 + y) * size + x1) * size + z;
	//		VertexInterp(isolevel, x1, y, z, x1, y1, z, voxels[x1][y][z], voxels[x1][y1][z], vertlist[9]);
	//	}
	//	if ((edgeTable[cubeindex] & 1024) != 0) {
	//		vertlist[10] = ((size * 2 - 2 + y) * size + x1) * size + z1;
	//		VertexInterp(isolevel, x1, y, z1, x1, y1, z1, voxels[x1][y][z1], voxels[x1][y1][z1], vertlist[10]);
	//	}
	//	if ((edgeTable[cubeindex] & 2048) != 0) {
	//		vertlist[11] = ((size * 2 - 2 + y) * size + x) * size + z1;
	//		VertexInterp(isolevel, x, y, z1, x, y1, z1, voxels[x][y][z1], voxels[x][y1][z1], vertlist[11]);
	//	}

	//	/* Create the triangle */
	//	ntriang = triTable[cubeindex].Length;
	//	if (ntriang <= 0) return null;
	//	int[] triangles = new int[ntriang];
	//	for (i = 0; i < ntriang; ++i) {
	//		triangles[i] = vertlist[triTable[cubeindex][i]];
	//	}

	//	return triangles;
	//}

	///*
	//	Linearly interpolate the position where an isosurface cuts
	//	an edge between two vertices, each with their own scalar value
	//*/
	//private void VertexInterp(float isolevel, int x1, int y1, int z1, int x2, int y2, int z2, float valp1, float valp2, int vox) {
	//	if (Mathf.Abs(isolevel-valp1) < 0.00001) {
	//		vertices[vox] = new Vector3(x1 * control.voxelSize, y1 * control.voxelSize, z1 * control.voxelSize);
	//		return;
	//	}
	//	if (Mathf.Abs(isolevel - valp2) < 0.00001) {
	//		vertices[vox] = new Vector3(x2 * control.voxelSize, y2 * control.voxelSize, z2 * control.voxelSize);
	//		return;
	//	}
	//	if (Mathf.Abs(valp1 - valp2) < 0.00001) {
	//		vertices[vox] = new Vector3(x1 * control.voxelSize, y1 * control.voxelSize, z1 * control.voxelSize);
	//		return;
	//	}

	//	float mu = (isolevel - valp1) / (valp2 - valp1);
	//	vertices[vox] = new Vector3(x1 + mu * (x2 - x1), y1 + mu * (y2 - y1), z1 + mu * (z2 - z1)) *control.voxelSize;
	//}

	//struct GRIDCELL {
	//	public Vector3[] p;
	//	public float[] val;
	//	public static GRIDCELL Default() {
	//		return new GRIDCELL() { p = new Vector3[8], val = new float[8] };
	//	}
	//};

	//static int[] edgeTable = {
	//		0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
	//		0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
	//		0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
	//		0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
	//		0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
	//		0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
	//		0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
	//		0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
	//		0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
	//		0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
	//		0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
	//		0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
	//		0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
	//		0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
	//		0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
	//		0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
	//		0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
	//		0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
	//		0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
	//		0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
	//		0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
	//		0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
	//		0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
	//		0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
	//		0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
	//		0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
	//		0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
	//		0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
	//		0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
	//		0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
	//		0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
	//		0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };
	//static int[][] triTable = {
	//		new int[] {},
	//		new int[] {0, 8, 3},
	//		new int[] {0, 1, 9},
	//		new int[] {1, 8, 3, 9, 8, 1},
	//		new int[] {1, 2, 10},
	//		new int[] {0, 8, 3, 1, 2, 10},
	//		new int[] {9, 2, 10, 0, 2, 9},
	//		new int[] {2, 8, 3, 2, 10, 8, 10, 9, 8},
	//		new int[] {3, 11, 2},
	//		new int[] {0, 11, 2, 8, 11, 0},
	//		new int[] {1, 9, 0, 2, 3, 11},
	//		new int[] {1, 11, 2, 1, 9, 11, 9, 8, 11},
	//		new int[] {3, 10, 1, 11, 10, 3},
	//		new int[] {0, 10, 1, 0, 8, 10, 8, 11, 10},
	//		new int[] {3, 9, 0, 3, 11, 9, 11, 10, 9},
	//		new int[] {9, 8, 10, 10, 8, 11},
	//		new int[] {4, 7, 8},
	//		new int[] {4, 3, 0, 7, 3, 4},
	//		new int[] {0, 1, 9, 8, 4, 7},
	//		new int[] {4, 1, 9, 4, 7, 1, 7, 3, 1},
	//		new int[] {1, 2, 10, 8, 4, 7},
	//		new int[] {3, 4, 7, 3, 0, 4, 1, 2, 10},
	//		new int[] {9, 2, 10, 9, 0, 2, 8, 4, 7},
	//		new int[] {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4},
	//		new int[] {8, 4, 7, 3, 11, 2},
	//		new int[] {11, 4, 7, 11, 2, 4, 2, 0, 4},
	//		new int[] {9, 0, 1, 8, 4, 7, 2, 3, 11},
	//		new int[] {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1},
	//		new int[] {3, 10, 1, 3, 11, 10, 7, 8, 4},
	//		new int[] {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4},
	//		new int[] {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3},
	//		new int[] {4, 7, 11, 4, 11, 9, 9, 11, 10},
	//		new int[] {9, 5, 4},
	//		new int[] {9, 5, 4, 0, 8, 3},
	//		new int[] {0, 5, 4, 1, 5, 0},
	//		new int[] {8, 5, 4, 8, 3, 5, 3, 1, 5},
	//		new int[] {1, 2, 10, 9, 5, 4},
	//		new int[] {3, 0, 8, 1, 2, 10, 4, 9, 5},
	//		new int[] {5, 2, 10, 5, 4, 2, 4, 0, 2},
	//		new int[] {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8},
	//		new int[] {9, 5, 4, 2, 3, 11},
	//		new int[] {0, 11, 2, 0, 8, 11, 4, 9, 5},
	//		new int[] {0, 5, 4, 0, 1, 5, 2, 3, 11},
	//		new int[] {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5},
	//		new int[] {10, 3, 11, 10, 1, 3, 9, 5, 4},
	//		new int[] {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10},
	//		new int[] {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3},
	//		new int[] {5, 4, 8, 5, 8, 10, 10, 8, 11},
	//		new int[] {9, 7, 8, 5, 7, 9},
	//		new int[] {9, 3, 0, 9, 5, 3, 5, 7, 3},
	//		new int[] {0, 7, 8, 0, 1, 7, 1, 5, 7},
	//		new int[] {1, 5, 3, 3, 5, 7},
	//		new int[] {9, 7, 8, 9, 5, 7, 10, 1, 2},
	//		new int[] {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3},
	//		new int[] {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2},
	//		new int[] {2, 10, 5, 2, 5, 3, 3, 5, 7},
	//		new int[] {7, 9, 5, 7, 8, 9, 3, 11, 2},
	//		new int[] {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11},
	//		new int[] {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7},
	//		new int[] {11, 2, 1, 11, 1, 7, 7, 1, 5},
	//		new int[] {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11},
	//		new int[] {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0},
	//		new int[] {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0},
	//		new int[] {11, 10, 5, 7, 11, 5},
	//		new int[] {10, 6, 5},
	//		new int[] {0, 8, 3, 5, 10, 6},
	//		new int[] {9, 0, 1, 5, 10, 6},
	//		new int[] {1, 8, 3, 1, 9, 8, 5, 10, 6},
	//		new int[] {1, 6, 5, 2, 6, 1},
	//		new int[] {1, 6, 5, 1, 2, 6, 3, 0, 8},
	//		new int[] {9, 6, 5, 9, 0, 6, 0, 2, 6},
	//		new int[] {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8},
	//		new int[] {2, 3, 11, 10, 6, 5},
	//		new int[] {11, 0, 8, 11, 2, 0, 10, 6, 5},
	//		new int[] {0, 1, 9, 2, 3, 11, 5, 10, 6},
	//		new int[] {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11},
	//		new int[] {6, 3, 11, 6, 5, 3, 5, 1, 3},
	//		new int[] {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6},
	//		new int[] {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9},
	//		new int[] {6, 5, 9, 6, 9, 11, 11, 9, 8},
	//		new int[] {5, 10, 6, 4, 7, 8},
	//		new int[] {4, 3, 0, 4, 7, 3, 6, 5, 10},
	//		new int[] {1, 9, 0, 5, 10, 6, 8, 4, 7},
	//		new int[] {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4},
	//		new int[] {6, 1, 2, 6, 5, 1, 4, 7, 8},
	//		new int[] {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7},
	//		new int[] {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6},
	//		new int[] {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9},
	//		new int[] {3, 11, 2, 7, 8, 4, 10, 6, 5},
	//		new int[] {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11},
	//		new int[] {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6},
	//		new int[] {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6},
	//		new int[] {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6},
	//		new int[] {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11},
	//		new int[] {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7},
	//		new int[] {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9},
	//		new int[] {10, 4, 9, 6, 4, 10},
	//		new int[] {4, 10, 6, 4, 9, 10, 0, 8, 3},
	//		new int[] {10, 0, 1, 10, 6, 0, 6, 4, 0},
	//		new int[] {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10},
	//		new int[] {1, 4, 9, 1, 2, 4, 2, 6, 4},
	//		new int[] {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4},
	//		new int[] {0, 2, 4, 4, 2, 6},
	//		new int[] {8, 3, 2, 8, 2, 4, 4, 2, 6},
	//		new int[] {10, 4, 9, 10, 6, 4, 11, 2, 3},
	//		new int[] {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6},
	//		new int[] {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10},
	//		new int[] {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1},
	//		new int[] {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3},
	//		new int[] {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1},
	//		new int[] {3, 11, 6, 3, 6, 0, 0, 6, 4},
	//		new int[] {6, 4, 8, 11, 6, 8},
	//		new int[] {7, 10, 6, 7, 8, 10, 8, 9, 10},
	//		new int[] {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10},
	//		new int[] {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0},
	//		new int[] {10, 6, 7, 10, 7, 1, 1, 7, 3},
	//		new int[] {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7},
	//		new int[] {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9},
	//		new int[] {7, 8, 0, 7, 0, 6, 6, 0, 2},
	//		new int[] {7, 3, 2, 6, 7, 2},
	//		new int[] {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7},
	//		new int[] {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7},
	//		new int[] {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11},
	//		new int[] {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1},
	//		new int[] {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6},
	//		new int[] {0, 9, 1, 11, 6, 7},
	//		new int[] {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0},
	//		new int[] {7, 11, 6},
	//		new int[] {7, 6, 11},
	//		new int[] {3, 0, 8, 11, 7, 6},
	//		new int[] {0, 1, 9, 11, 7, 6},
	//		new int[] {8, 1, 9, 8, 3, 1, 11, 7, 6},
	//		new int[] {10, 1, 2, 6, 11, 7},
	//		new int[] {1, 2, 10, 3, 0, 8, 6, 11, 7},
	//		new int[] {2, 9, 0, 2, 10, 9, 6, 11, 7},
	//		new int[] {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8},
	//		new int[] {7, 2, 3, 6, 2, 7},
	//		new int[] {7, 0, 8, 7, 6, 0, 6, 2, 0},
	//		new int[] {2, 7, 6, 2, 3, 7, 0, 1, 9},
	//		new int[] {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6},
	//		new int[] {10, 7, 6, 10, 1, 7, 1, 3, 7},
	//		new int[] {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8},
	//		new int[] {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7},
	//		new int[] {7, 6, 10, 7, 10, 8, 8, 10, 9},
	//		new int[] {6, 8, 4, 11, 8, 6},
	//		new int[] {3, 6, 11, 3, 0, 6, 0, 4, 6},
	//		new int[] {8, 6, 11, 8, 4, 6, 9, 0, 1},
	//		new int[] {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6},
	//		new int[] {6, 8, 4, 6, 11, 8, 2, 10, 1},
	//		new int[] {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6},
	//		new int[] {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9},
	//		new int[] {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3},
	//		new int[] {8, 2, 3, 8, 4, 2, 4, 6, 2},
	//		new int[] {0, 4, 2, 4, 6, 2},
	//		new int[] {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8},
	//		new int[] {1, 9, 4, 1, 4, 2, 2, 4, 6},
	//		new int[] {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1},
	//		new int[] {10, 1, 0, 10, 0, 6, 6, 0, 4},
	//		new int[] {4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3},
	//		new int[] {10, 9, 4, 6, 10, 4},
	//		new int[] {4, 9, 5, 7, 6, 11},
	//		new int[] {0, 8, 3, 4, 9, 5, 11, 7, 6},
	//		new int[] {5, 0, 1, 5, 4, 0, 7, 6, 11},
	//		new int[] {11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5},
	//		new int[] {9, 5, 4, 10, 1, 2, 7, 6, 11},
	//		new int[] {6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5},
	//		new int[] {7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2},
	//		new int[] {3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6},
	//		new int[] {7, 2, 3, 7, 6, 2, 5, 4, 9},
	//		new int[] {9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7},
	//		new int[] {3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0},
	//		new int[] {6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8},
	//		new int[] {9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7},
	//		new int[] {1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4},
	//		new int[] {4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10},
	//		new int[] {7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10},
	//		new int[] {6, 9, 5, 6, 11, 9, 11, 8, 9},
	//		new int[] {3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5},
	//		new int[] {0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11},
	//		new int[] {6, 11, 3, 6, 3, 5, 5, 3, 1},
	//		new int[] {1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6},
	//		new int[] {0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10},
	//		new int[] {11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5},
	//		new int[] {6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3},
	//		new int[] {5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2},
	//		new int[] {9, 5, 6, 9, 6, 0, 0, 6, 2},
	//		new int[] {1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8},
	//		new int[] {1, 5, 6, 2, 1, 6},
	//		new int[] {1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6},
	//		new int[] {10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0},
	//		new int[] {0, 3, 8, 5, 6, 10},
	//		new int[] {10, 5, 6},
	//		new int[] {11, 5, 10, 7, 5, 11},
	//		new int[] {11, 5, 10, 11, 7, 5, 8, 3, 0},
	//		new int[] {5, 11, 7, 5, 10, 11, 1, 9, 0},
	//		new int[] {10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1},
	//		new int[] {11, 1, 2, 11, 7, 1, 7, 5, 1},
	//		new int[] {0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11},
	//		new int[] {9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7},
	//		new int[] {7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2},
	//		new int[] {2, 5, 10, 2, 3, 5, 3, 7, 5},
	//		new int[] {8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5},
	//		new int[] {9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2},
	//		new int[] {9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2},
	//		new int[] {1, 3, 5, 3, 7, 5},
	//		new int[] {0, 8, 7, 0, 7, 1, 1, 7, 5},
	//		new int[] {9, 0, 3, 9, 3, 5, 5, 3, 7},
	//		new int[] {9, 8, 7, 5, 9, 7},
	//		new int[] {5, 8, 4, 5, 10, 8, 10, 11, 8},
	//		new int[] {5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0},
	//		new int[] {0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5},
	//		new int[] {10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4},
	//		new int[] {2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8},
	//		new int[] {0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11},
	//		new int[] {0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5},
	//		new int[] {9, 4, 5, 2, 11, 3},
	//		new int[] {2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4},
	//		new int[] {5, 10, 2, 5, 2, 4, 4, 2, 0},
	//		new int[] {3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9},
	//		new int[] {5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2},
	//		new int[] {8, 4, 5, 8, 5, 3, 3, 5, 1},
	//		new int[] {0, 4, 5, 1, 0, 5},
	//		new int[] {8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5},
	//		new int[] {9, 4, 5},
	//		new int[] {4, 11, 7, 4, 9, 11, 9, 10, 11},
	//		new int[] {0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11},
	//		new int[] {1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11},
	//		new int[] {3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4},
	//		new int[] {4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2},
	//		new int[] {9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3},
	//		new int[] {11, 7, 4, 11, 4, 2, 2, 4, 0},
	//		new int[] {11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4},
	//		new int[] {2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9},
	//		new int[] {9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7},
	//		new int[] {3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10},
	//		new int[] {1, 10, 2, 8, 7, 4},
	//		new int[] {4, 9, 1, 4, 1, 7, 7, 1, 3},
	//		new int[] {4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1},
	//		new int[] {4, 0, 3, 7, 4, 3},
	//		new int[] {4, 8, 7},
	//		new int[] {9, 10, 8, 10, 11, 8},
	//		new int[] {3, 0, 9, 3, 9, 11, 11, 9, 10},
	//		new int[] {0, 1, 10, 0, 10, 8, 8, 10, 11},
	//		new int[] {3, 1, 10, 11, 3, 10},
	//		new int[] {1, 2, 11, 1, 11, 9, 9, 11, 8},
	//		new int[] {3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9},
	//		new int[] {0, 2, 11, 8, 0, 11},
	//		new int[] {3, 2, 11},
	//		new int[] {2, 3, 8, 2, 8, 10, 10, 8, 9},
	//		new int[] {9, 10, 2, 0, 9, 2},
	//		new int[] {2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8},
	//		new int[] {1, 10, 2},
	//		new int[] {1, 3, 8, 9, 1, 8},
	//		new int[] {0, 9, 1},
	//		new int[] {0, 3, 8},
	//		new int[] {}};
}
