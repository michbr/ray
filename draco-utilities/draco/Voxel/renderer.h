
#ifndef DRACO_VOX_RENDERER_H
#define DRACO_VOX_RENDERER_H

static Dictionary<int, object> vertices;
static Dictionary<int, byte> materials;
static float voxelSize;
static int[] vertlist = new int[12];
static byte isolevel;
static Voxel[, ,] voxels;
static Vector3 offset;
static Vector3[] meshVerts;
public const byte MIDDLE_LEVEL = 128;

/*
 * MUST BE CALLED BEFORE polygonize!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
public static void setup(float voxelSize, byte isolevel, ref Dictionary<int, object> vertices, ref Dictionary<int, byte> materials, ref Voxel[, ,] voxels, Vector3 offset, Vector3[] meshVerts) {
MarchingCubesV2.isolevel = isolevel;
MarchingCubesV2.vertices = vertices;
MarchingCubesV2.materials = materials;
MarchingCubesV2.voxels = voxels;
MarchingCubesV2.voxelSize = voxelSize;
MarchingCubesV2.offset = offset;
MarchingCubesV2.meshVerts = meshVerts;
}

/*
	Given a grid cell and an isolevel, calculate the triangular
	facets required to represent the isosurface through the cell.
	Return the number of triangular facets, the array "triangles"
	will be loaded up with the vertices at most 5 triangular facets.
	0 will be returned if the grid cell is either totally above
	or totally below the isolevel.
*/
public static int[] lookupTriangles(int x, int y, int z, int x1, int y1, int z1) {
	/*
		Determine the index into the edge table which
		tells us which vertices are inside of the surface
	*/
	int cubeindex = 0;
	if (voxels[x, y, z].opacity < isolevel) cubeindex |= 1;
	if (voxels[x1, y, z].opacity < isolevel) cubeindex |= 2;
	if (voxels[x1, y, z1].opacity < isolevel) cubeindex |= 4;
	if (voxels[x, y, z1].opacity < isolevel) cubeindex |= 8;
	if (voxels[x, y1, z].opacity < isolevel) cubeindex |= 16;
	if (voxels[x1, y1, z].opacity < isolevel) cubeindex |= 32;
	if (voxels[x1, y1, z1].opacity < isolevel) cubeindex |= 64;
	if (voxels[x, y1, z1].opacity < isolevel) cubeindex |= 128;

	/* Cube is entirely in/out of the surface */
	if (edgeTable[cubeindex] == 0)
		return null;

	/* Find the vertices where the surface intersects the cube */
	if ((edgeTable[cubeindex] & 1) != 0) {
		vertlist[0] = VoxelRenderer.getX(x, y, z);
		stretchVertex(x, y, z, x1, y, z, voxels[x, y, z], voxels[x1, y, z], vertlist[0]);
	}
	if ((edgeTable[cubeindex] & 2) != 0) {
		vertlist[1] = VoxelRenderer.getZ(x1, y, z);
		stretchVertex(x1, y, z, x1, y, z1, voxels[x1, y, z], voxels[x1, y, z1], vertlist[1]);
	}
	if ((edgeTable[cubeindex] & 4) != 0) {
		vertlist[2] = VoxelRenderer.getX(x, y, z1);
		stretchVertex(x1, y, z1, x, y, z1, voxels[x1, y, z1], voxels[x, y, z1], vertlist[2]);
	}
	if ((edgeTable[cubeindex] & 8) != 0) {
		vertlist[3] = VoxelRenderer.getZ(x, y, z);
		stretchVertex(x, y, z1, x, y, z, voxels[x, y, z1], voxels[x, y, z], vertlist[3]);
	}
	if ((edgeTable[cubeindex] & 16) != 0) {
		vertlist[4] = VoxelRenderer.getX(x, y1, z);
		stretchVertex(x, y1, z, x1, y1, z, voxels[x, y1, z], voxels[x1, y1, z], vertlist[4]);
	}
	if ((edgeTable[cubeindex] & 32) != 0) {
		vertlist[5] = VoxelRenderer.getZ(x1, y1, z);
		stretchVertex(x1, y1, z, x1, y1, z1, voxels[x1, y1, z], voxels[x1, y1, z1], vertlist[5]);
	}
	if ((edgeTable[cubeindex] & 64) != 0) {
		vertlist[6] = VoxelRenderer.getX(x, y1, z1);
		stretchVertex(x1, y1, z1, x, y1, z1, voxels[x1, y1, z1], voxels[x, y1, z1], vertlist[6]);
	}
	if ((edgeTable[cubeindex] & 128) != 0) {
		vertlist[7] = VoxelRenderer.getZ(x, y1, z);
		stretchVertex(x, y1, z1, x, y1, z, voxels[x, y1, z1], voxels[x, y1, z], vertlist[7]);
	}
	if ((edgeTable[cubeindex] & 256) != 0) {
		vertlist[8] = VoxelRenderer.getY(x, y, z);
		stretchVertex(x, y, z, x, y1, z, voxels[x, y, z], voxels[x, y1, z], vertlist[8]);
	}
	if ((edgeTable[cubeindex] & 512) != 0) {
		vertlist[9] = VoxelRenderer.getY(x1, y, z);
		stretchVertex(x1, y, z, x1, y1, z, voxels[x1, y, z], voxels[x1, y1, z], vertlist[9]);
	}
	if ((edgeTable[cubeindex] & 1024) != 0) {
		vertlist[10] = VoxelRenderer.getY(x1, y, z1);
		stretchVertex(x1, y, z1, x1, y1, z1, voxels[x1, y, z1], voxels[x1, y1, z1], vertlist[10]);
	}
	if ((edgeTable[cubeindex] & 2048) != 0) {
		vertlist[11] = VoxelRenderer.getY(x, y, z1);
		stretchVertex(x, y, z1, x, y1, z1, voxels[x, y, z1], voxels[x, y1, z1], vertlist[11]);
	}

	/* Create the triangles */
	int ntriang = triTable[cubeindex].Length;
	if (ntriang <= 0) return null;
	int[] triangles = new int[ntriang];
	    for (int i = 0; i < ntriang; ++i) {
		    triangles[ntriang - i - 1] = vertlist[triTable[cubeindex][i]];
	    }

	    return triangles;
	}

/*
	Linearly interpolate the position where an isosurface cuts
	an edge between two vertices, each with their own scalar value
*/
public static void stretchVertex(int x1, int y1, int z1, int x2, int y2, int z2, Voxel valp1, Voxel valp2, int vox) {
	float mu = (isolevel - valp1.opacity) / ((float)(valp2.opacity - valp1.opacity));
	//float mu = 0.5f;
	Vector3 pos = new Vector3(x1 + mu * (x2 - x1), y1 + mu * (y2 - y1), z1 + mu * (z2 - z1)) * voxelSize + offset;
	if (vertices.ContainsKey(vox) && vertices[vox].GetType() == typeof(int))
	meshVerts[(int)vertices[vox]] = pos;
	else
	vertices[vox] = pos;
	if (valp1.opacity > valp2.opacity)
		materials[vox] = valp1.matType;
	else
		materials[vox] = valp2.matType;
	//vertices[vox] = new Vector3(x1, y1, z1) *voxelSize +offset;
	//float mu = (valp1) / ((float)(byte.MaxValue));
	//vertices[vox] = new Vector3(x1 + mu * (x2 - x1), y1 + mu * (y2 - y1), z1 + mu * (z2 - z1)) * voxelSize;
}

static int[] edgeTable = {
	0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
	0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
	0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
	0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
	0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
	0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
	0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
	0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
	0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
	0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
	0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
	0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
	0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
	0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
	0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
	0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
	0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
	0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
	0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
	0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
	0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
	0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
	0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
	0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
	0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
	0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
	0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
	0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
	0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
	0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
	0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
	0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };
static int[][] triTable = {
}


#endif // DRACO_VOX_RENDERER_H