using UnityEngine;
using System.Collections;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Collections.Generic;

namespace Vox {

	[AddComponentMenu("Scripts/Voxel/VoxelTerrain")]
	[ExecuteInEditMode]
	public class VoxelTerrain : VoxelControlV2 {

		public string data_file;

		public Texture2D heightmap;
		public Texture2D materialMap;

		//void Update() {

		//}

		void Awake() {
			if (Application.isPlaying)
				initializeHeightmap();
		}

		public void initializeHeightmap() {

			head = new VoxelBlock();
			maxDetail = (byte)Mathf.Log(heightmap.height, 2);

			sizes = new float[maxDetail + 1];
			float s = BaseSize;
			for (int i = 0; i <= maxDetail; ++i) {
				sizes[i] = s;
				s /= 2;
			}
			cam = GameObject.FindGameObjectWithTag("Player").GetComponentInChildren<Camera>();
			if (Application.isPlaying && GetComponent<MineVoxelEvent>() == null)
				gameObject.AddComponent<MineVoxelEvent>();
			loadData();

			applyRenderers();

			updateLocalCamPosition();

			//head.updateAll(0, 0, 0, 0);
			enqueueCheck(new UpdateCheckJob(head, this, 0));
			//checkQueued();
			//updateQueued();
		}

		public virtual void loadData() {
			int voxels = heightmap.height;

			float[,] map = new float[voxels, voxels];
			//print(heightmap.height);
			//print(heightmap.width);
			for (int i = 0; i < heightmap.height; i++) {
				for (int j = 0; j < heightmap.width; j++) {
					Color pix = heightmap.GetPixel((heightmap.height - 1) - i, j);
					map[j, i] = ((pix.r + pix.g + pix.b) / 3.0f) * voxels;
					//print("h: " + map[i,j]);
					//float two = pix.g;
				}
			}
			//print(map);
			//print("maxdet: " + ((byte)Mathf.Log((voxels / 16), 2)+1));
			//head.setToHeightmap((byte)(Mathf.Log(voxels/16, 2)+2), 0, 0, 0, ref map);
			if (materialMap == null)
				head.setToHeightmap(maxDetail, 0, 0, 0, ref map, 0, this);
			else {
				byte[,] matMap = new byte[voxels, voxels];
				for (int i = 0; i < materialMap.height; i++) {
					for (int j = 0; j < materialMap.width; j++) {
						Color pix = materialMap.GetPixel((materialMap.height - 1) - i, j);
						matMap[j, i] = (byte)(((pix.r + pix.g + pix.b) / 3.0f) * voxelMaterials.Length);
					}
				}
				head.setToHeightmap(maxDetail, 0, 0, 0, ref map, matMap, this);
			}
			/*if (File.Exists(Application.persistentDataPath + "/heightmap.dat")) {
				BinaryFormatter b = new BinaryFormatter();
				//Get the file
				FileStream f = File.Open(Application.persistentDataPath + "/heightmap.dat", FileMode.Open);
				//Load back the scores
				//heightmap = (List<ScoreEntry>)b.Deserialize(f);
				f.Close();
			}*/
		}

		public void saveData() {
			BinaryFormatter b = new BinaryFormatter();
			FileStream f = File.Create(Application.persistentDataPath + "/heightmap.dat");
			b.Serialize(f, heightmap);
			f.Close();
		}

		public Vector3 getPath(Vector3 from, Vector3 to) {
			Vector3 dir = to - from;
			//float f = from.x / sizes[maxDetail];
			print("size: " + sizes[maxDetail]);
			float x = Mathf.Round(from.x/sizes[maxDetail]);
			float y = Mathf.Round(from.y/sizes[maxDetail]);
			float z = Mathf.Round(from.z/sizes[maxDetail]);
			print("Cur. Voxel: (" + x + ", " + y + ", " + z + ")");
			dir.Normalize();
			print("dir: " +dir);
			if (Mathf.Abs(dir.x) > Mathf.Abs(dir.y) && Mathf.Abs(dir.x) > Mathf.Abs(dir.z)) {

				if (dir.x < 0) {
					print("x--");
					x--;
				}
				else {
					print("x++");
					x++;
				}
			}
			else if (Mathf.Abs(dir.y) > Mathf.Abs(dir.z)) {
				if (dir.y < 0) {
					print("y--");
					y--;
				}
				else {
					print("y++");
					y++;
				}
			}
			else {
				if (dir.z < 0) {
					print("z--");
					z--;
				}
				else { 
					z++;
					print("z++");
				}
			}
			print("(" + x + ", " + y + ", " + z + ")");
			VoxelHolder b = head.get(maxDetail, (int)x, (int)y, (int)z);
			if (b.averageOpacity() < .001) {
				return ((new Vector3(x * sizes[maxDetail], y * sizes[maxDetail], z * sizes[maxDetail])) - from).normalized;
			}
			return new Vector3(0f, 0f, 0f);
		}

		/*public pathNode getNext(Vector3 from, Vector3 to) {
			Vector3 dir = to - from;
			//float f = from.x / sizes[maxDetail];
			//print("size: " + sizes[maxDetail]);
			float x = Mathf.Round(from.x / sizes[maxDetail]);
			float y = Mathf.Round(from.y / sizes[maxDetail]);
			float z = Mathf.Round(from.z / sizes[maxDetail]);
			//print("Cur. Voxel: (" + x + ", " + y + ", " + z + ")");
			dir.Normalize();
		//	print("dir: " + dir);
			if (Mathf.Abs(dir.x) > Mathf.Abs(dir.y) && Mathf.Abs(dir.x) > Mathf.Abs(dir.z)) {

				if (dir.x < 0) {
				//	print("x--");
					x--;
				}
				else {
				//	print("x++");
					x++;
				}
			}
			else if (Mathf.Abs(dir.y) > Mathf.Abs(dir.z)) {
				if (dir.y < 0) {
			//		print("y--");
					y--;
				}
				else {
				//	print("y++");
					y++;
				}
			}
			else {
				if (dir.z < 0) {
			//		print("z--");
					z--;
				}
				else {
					z++;
				//	print("z++");
				}
			}
			//print("(" + x + ", " + y + ", " + z + ")");
			VoxelHolder b = head.get(maxDetail, (int)x, (int)y, (int)z);
			if (b.averageOpacity() < .001) {
				pathNode temp = new pathNode();
				temp.setPos(new Vector3(x, y, z));
				return temp;
			}
			return null;
		}*/

		public bool isEmpty (pathNode place) {
			VoxelHolder b = head.get((byte)(maxDetail), (int)place.getPos().x, (int)place.getPos().y, (int)place.getPos().z);
			return b.averageOpacity() < 40;
		}
	}

}