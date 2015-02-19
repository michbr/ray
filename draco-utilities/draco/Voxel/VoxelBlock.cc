
namespace Vox {

	public class VoxelBlock : VoxelHolder {

		public static int totalConsolidations = 0;
		public static int skippedSubdivisions = 0;
		public const byte CHILD_COUNT_POWER = 1;
		public const int CHILD_DIMENSION = 1 << (CHILD_COUNT_POWER);

		public VoxelHolder[, ,] children;
		public VoxelRenderer renderer;

		public VoxelBlock(Voxel fillValue) {
			children = new VoxelHolder[CHILD_DIMENSION, CHILD_DIMENSION, CHILD_DIMENSION];
			++blockCount;
			set(fillValue);
		}

		public VoxelBlock() : this(Voxel.empty) { }

		public void set(Voxel fillValue) {
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi)
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi)
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi)
						children[xi, yi, zi] = fillValue;
		}

		public void set(byte detailLevel, int x, int y, int z, Voxel value, VoxelControlV2 control) {
			if (detailLevel > 0) {
				short factor = (short)(1 << (detailLevel - CHILD_COUNT_POWER));
				byte xi = (byte)(x / factor);
				byte yi = (byte)(y / factor);
				byte zi = (byte)(z / factor);
				if (detailLevel == CHILD_COUNT_POWER) {
					children[xi, yi, zi] = value;
				} else {
					if (children[xi, yi, zi].GetType() == typeof(Voxel)) {
						if (children[xi, yi, zi].Equals(value)) { ++skippedSubdivisions; return; }
						children[xi, yi, zi] = new VoxelBlock((Voxel)children[xi, yi, zi]);
					}
					((VoxelBlock)children[xi, yi, zi]).set((byte)(detailLevel - CHILD_COUNT_POWER), x - xi * factor, y - yi * factor, z - zi * factor, value, control);
				}
			} else
				set(value);
		}

		public override VoxelHolder get(byte detailLevel, int x, int y, int z) {

			if (detailLevel > 0) {
				short factor = (short)(1 << (detailLevel - CHILD_COUNT_POWER));
				byte xi = (byte)(x / factor);
				byte yi = (byte)(y / factor);
				byte zi = (byte)(z / factor);
				if (detailLevel == CHILD_COUNT_POWER)
					return children[xi, yi, zi];
				return children[xi, yi, zi].get((byte)(detailLevel - CHILD_COUNT_POWER), x - xi * factor, y - yi * factor, z - zi * factor);
			} else
				return this;
		}

		public override byte detail() {
			byte detail = 0;
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi)
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi)
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi)
						detail = (byte)Mathf.Max(detail, children[xi, yi, zi].detail());
			return (byte)(detail + 1);
		}

		public override byte averageOpacity() {
			short totalOpacity = 0;
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi)
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi)
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi)
						totalOpacity += children[xi, yi, zi].averageOpacity();

			return (byte)(totalOpacity / (float)(CHILD_DIMENSION << (CHILD_COUNT_POWER * 2)));
		}

		public override byte averageMaterialType() {
			short totalMats = 0;
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi)
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi)
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi)
						totalMats += children[xi, yi, zi].averageMaterialType();

			return (byte)(totalMats / (float)(CHILD_DIMENSION << (CHILD_COUNT_POWER * 2)) + 0.5f);
		}

		public override Voxel toVoxel() {
			return new Voxel(averageMaterialType(), averageOpacity());
		}

		public void setToHeightmap(byte detailLevel, int x, int y, int z, ref float[,] map, byte material, VoxelControlV2 control) {
			if (detailLevel <= CHILD_COUNT_POWER) {
				for (int xi = 0; xi < CHILD_DIMENSION; ++xi) {
					for (int zi = 0; zi < CHILD_DIMENSION; ++zi) {
						for (int yi = 0; yi < CHILD_DIMENSION; ++yi) {
							if (yi + y >= map[x + xi, z + zi])
								break;
							else if (material == byte.MaxValue) {
								children[xi, yi, zi] = Voxel.empty;
							} else {
								if (yi + y >= map[x + xi, z + zi] - 1) {
									byte opacity = (byte)((map[x + xi, z + zi] - yi - y) * byte.MaxValue);
									if (opacity > control.isoLevel || children[xi, yi, zi].averageOpacity() <= opacity)
										children[xi, yi, zi] = new Voxel(material, opacity);
								} else {
									children[xi, yi, zi] = new Voxel(material, byte.MaxValue);
								}
							}
						}
					}
				}
			} else {
				int multiplier = (1 << (detailLevel - CHILD_COUNT_POWER));
				for (int xi = 0; xi < CHILD_DIMENSION; ++xi) {
					for (int zi = 0; zi < CHILD_DIMENSION; ++zi) {
						int xMax = x + (xi + 1) * multiplier;
						int zMax = z + (zi + 1) * multiplier;
						float yMin = float.MaxValue;
						float yMax = 0;
						for (int xPos = x + xi * multiplier; xPos < xMax; ++xPos) {
							for (int zPos = z + zi * multiplier; zPos < zMax; ++zPos) {
								if (map[xPos, zPos] < yMin) yMin = map[xPos, zPos];
								if (map[xPos, zPos] > yMax) yMax = map[xPos, zPos];
							}
						}

						int firstUnsolidBlock = Mathf.Min(((int)(yMin - y)) / multiplier, CHILD_DIMENSION);
						int lastUnsolidBlock = Mathf.Min(((int)(yMax - y)) / multiplier, CHILD_DIMENSION - 1);
						int yi = 0;
						for (; yi < firstUnsolidBlock; ++yi) {
							if (material == byte.MaxValue)
								children[xi, yi, zi] = Voxel.empty;
							else
								children[xi, yi, zi] = new Voxel(material, byte.MaxValue);
						}
						if (lastUnsolidBlock < 0) continue;
						for (; yi <= lastUnsolidBlock; ++yi) {
							if (children[xi, yi, zi].GetType() == typeof(Voxel))
								children[xi, yi, zi] = new VoxelBlock((Voxel)children[xi, yi, zi]);
							((VoxelBlock)children[xi, yi, zi]).setToHeightmap((byte)(detailLevel - CHILD_COUNT_POWER), x + xi * multiplier, y + yi * multiplier, z + zi * multiplier, ref map, material, control);
						}
					}
				}
			}
		}

		public void setToHeightmap(byte detailLevel, int x, int y, int z, ref float[,] map, byte[,] mats, VoxelControlV2 control) {
			if (detailLevel <= CHILD_COUNT_POWER) {
				for (int xi = 0; xi < CHILD_DIMENSION; ++xi) {
					for (int zi = 0; zi < CHILD_DIMENSION; ++zi) {
						for (int yi = 0; yi < CHILD_DIMENSION; ++yi) {
							if (yi + y >= map[x + xi, z + zi])
								break;
							else if (yi + y >= map[x + xi, z + zi] - 1) {
								if (mats[x + xi, z + zi] == byte.MaxValue)
									children[xi, yi, zi] = Voxel.empty;
								else
									children[xi, yi, zi] = new Voxel(mats[x + xi, z + zi], (byte)((map[x + xi, z + zi] - yi - y) * byte.MaxValue));
							} else {
								if (mats[x + xi, z + zi] == byte.MaxValue)
									children[xi, yi, zi] = Voxel.empty;
								else
									children[xi, yi, zi] = new Voxel(mats[x + xi, z + zi], byte.MaxValue);
							}
						}
					}
				}
			} else {
				int multiplier = (1 << (detailLevel - CHILD_COUNT_POWER));
				for (int xi = 0; xi < CHILD_DIMENSION; ++xi) {
					for (int zi = 0; zi < CHILD_DIMENSION; ++zi) {
						int xMax = x + (xi + 1) * multiplier;
						int zMax = z + (zi + 1) * multiplier;
						float yMin = float.MaxValue;
						float yMax = 0;
						bool multipleMaterials = false;
						byte material = mats[x, z];
						for (int xPos = x + xi * multiplier; xPos < xMax; ++xPos) {
							for (int zPos = z + zi * multiplier; zPos < zMax; ++zPos) {
								if (map[xPos, zPos] < yMin) yMin = map[xPos, zPos];
								if (map[xPos, zPos] > yMax) yMax = map[xPos, zPos];
								if (mats[xPos, zPos] != material) multipleMaterials = true;
							}
						}

						if (multipleMaterials) yMin = 0;
						int firstUnsolidBlock = Mathf.Min(((int)(yMin - y)) / multiplier, CHILD_DIMENSION);
						int lastUnsolidBlock = Mathf.Min(((int)(yMax - y)) / multiplier, CHILD_DIMENSION - 1);
						int yi = 0;
						for (; yi < firstUnsolidBlock; ++yi) {
							if (mats[x + xi * multiplier, z + zi * multiplier] == byte.MaxValue)
								children[xi, yi, zi] = Voxel.empty;
							else
								children[xi, yi, zi] = new Voxel(mats[x + xi * multiplier, z + zi * multiplier], byte.MaxValue);
						}
						if (lastUnsolidBlock < 0) continue;
						for (; yi <= lastUnsolidBlock; ++yi) {
							VoxelBlock newChild = new VoxelBlock();
							newChild.setToHeightmap((byte)(detailLevel - CHILD_COUNT_POWER), x + xi * multiplier, y + yi * multiplier, z + zi * multiplier, ref map, mats, control);
							children[xi, yi, zi] = newChild;
						}
					}
				}
			}
		}

		//public void setSphere(VoxelUpdateInfo info, byte detailLevel, Vector3 min, Vector3 max, Voxel value, VoxelControlV2 control) {
		//	int factor = 1 << (detailLevel - CHILD_COUNT_POWER);
		//	byte xiMin = (byte)Mathf.Max(min.x / factor - info.x * CHILD_DIMENSION, 0);
		//	byte xiMax = (byte)Mathf.Min((max.x + 3) / factor - info.x * CHILD_DIMENSION, CHILD_DIMENSION - 1);
		//	byte yiMin = (byte)Mathf.Max(min.y / factor - info.y * CHILD_DIMENSION, 0);
		//	byte yiMax = (byte)Mathf.Min((max.y + 3) / factor - info.y * CHILD_DIMENSION, CHILD_DIMENSION - 1);
		//	byte ziMin = (byte)Mathf.Max(min.z / factor - info.z * CHILD_DIMENSION, 0);
		//	byte ziMax = (byte)Mathf.Min((max.z + 3) / factor - info.z * CHILD_DIMENSION, CHILD_DIMENSION - 1);

		//	for (byte xi = xiMin; xi <= xiMax; ++xi) {
		//		for (byte yi = yiMin; yi <= yiMax; ++yi) {
		//			for (byte zi = ziMin; zi <= ziMax; ++zi) {
		//				if (detailLevel <= CHILD_COUNT_POWER) {
		//					children[xi, yi, zi] = Voxel.setSphere(children[xi, yi, zi], info.x * CHILD_DIMENSION + xi, info.y * CHILD_DIMENSION + yi, info.z * CHILD_DIMENSION + zi, min, max, value);
		//				} else {
		//					if (children[xi, yi, zi].GetType() == typeof(Voxel)) {
		//						children[xi, yi, zi] = new VoxelBlock((Voxel)children[xi, yi, zi]);
		//					}
		//					((VoxelBlock)children[xi, yi, zi]).setSphere(new VoxelUpdateInfo(info, xi, yi, zi), (byte)(detailLevel - CHILD_COUNT_POWER), min, max, value, control);
		//				}
		//			}
		//		}
		//	}

		//	// TODO: this should check if completely contained, not if rendersize (for distant modifications)
		//	if (isRenderSize(info.size, control) && info != null) {
		//		MonoBehaviour.print(info.x +", " +info.y +", " +info.z);
		//		updateAll(info.x, info.y, info.z, info.detailLevel, control, true);
		//		//myControl.checkQueued();
		//		//myControl.updateQueued();
		//	}
		//}

		public void updateAll(int x, int y, int z, byte detailLevel, VoxelControlV2 control, bool force = false) {
			// check if this is a high enough detail level.  If not, call the childrens' update methods
			if (!isRenderSize(control.sizes[detailLevel], control) && (!isRenderLod(x, y, z, control.sizes[detailLevel], control))) {
				for (byte xi = 0; xi < CHILD_DIMENSION; ++xi) {
					for (byte yi = 0; yi < CHILD_DIMENSION; ++yi) {
						for (byte zi = 0; zi < CHILD_DIMENSION; ++zi) {
							//VoxelUpdateInfo childInfo = new VoxelUpdateInfo(info, xi, yi, zi);
							if (children[xi, yi, zi].GetType() == typeof(Voxel)) {
								//if (!childInfo.isSolid())
								children[xi, yi, zi] = new VoxelBlock((Voxel)children[xi, yi, zi]);
								//else
								//continue;
							}
							UpdateCheckJob job = new UpdateCheckJob((VoxelBlock)children[xi, yi, zi], control, (byte)(detailLevel + 1));
							job.setOffset((byte)(x * CHILD_DIMENSION + xi), (byte)(y * CHILD_DIMENSION + yi), (byte)(z * CHILD_DIMENSION + zi));
							control.enqueueCheck(job);
						}
					}
				}
				if (renderer != null) {
					//GameObject.Destroy(renderer.ob);
					//lock (myControl) {
					//	myControl.enqueueJob(new DropRendererJob(renderer));
					//	renderer = null;
					//}
					renderer.old = true;
				}
				return;
			}

			// check if we already have a mesh
			if (renderer == null) {
				//clearSubRenderers();
				renderer = new VoxelRenderer(this, control, new Vector3(x * control.sizes[detailLevel], y * control.sizes[detailLevel], z * control.sizes[detailLevel]));
				//info.renderers[1, 1, 1] = renderer;
			} else {
				renderer.old = false;
				if (!force) return;
			}

			// We should generate a mesh
			GenMeshJob updateJob = new GenMeshJob(renderer.getBlock(), control, detailLevel);
			updateJob.setOffset(x, y, z);
			control.enqueueUpdate(updateJob);
		}

		public void clearSubRenderers(VoxelControlV2 control) {
			clearSubRenderers(true, control);
		}

		public void clearSubRenderers(bool clearSelf, VoxelControlV2 control) {
			if (clearSelf && renderer != null) {
				control.enqueueJob(new DropRendererJob(renderer));
				renderer = null;
				return;
			}
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi) {
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi) {
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi) {
						if (children[xi, yi, zi].GetType() != typeof(Voxel))
							((VoxelBlock)children[xi, yi, zi]).clearSubRenderers(true, control);
					}
				}
			}
		}

		public override VoxelRenderer getRenderer(byte detailLevel, int x, int y, int z) {
			if (renderer != null || detailLevel < 1) {
				return renderer;
			}
			short factor = (short)(1 << (detailLevel - CHILD_COUNT_POWER));
			byte xi = (byte)(x / factor);
			byte yi = (byte)(y / factor);
			byte zi = (byte)(z / factor);
			if (children[xi, yi, zi].GetType() == typeof(Voxel))
				return null;
			return children[xi, yi, zi].getRenderer((byte)(detailLevel - CHILD_COUNT_POWER), x - xi * factor, y - yi * factor, z - zi * factor);
		}

		public bool isRenderSize(float size, VoxelControlV2 control) {
			return control.sizes[control.maxDetail - VoxelRenderer.VOXEL_COUNT_POWER] == size;
		}

		public bool isRenderLod(float x, float y, float z, float size, VoxelControlV2 control) {
			if (!control.useLod)
				return size == control.sizes[control.maxDetail];
			return getDistSquare(control.getLocalCamPosition(), new Vector3(x + 0.5f, y + 0.5f, z + 0.5f), size) >= size * size * control.getLodDetail();
		}

		public void clearSuperRenderers(byte detailLevel, int x, int y, int z, VoxelControlV2 control) {
			if (detailLevel > 0) {
				short factor = (short)(1 << (detailLevel - CHILD_COUNT_POWER));
				byte xi = (byte)(x / factor);
				byte yi = (byte)(y / factor);
				byte zi = (byte)(z / factor);

				if (renderer != null && filledWithSubRenderers(false)) {
					control.enqueueJob(new DropRendererJob(renderer));
					renderer = null;
				}
				((VoxelBlock)children[xi, yi, zi]).clearSuperRenderers((byte)(detailLevel - CHILD_COUNT_POWER), x - xi * factor, y - yi * factor, z - zi * factor, control);
			}
		}

		private bool filledWithSubRenderers(bool checkSelf) {
			if (checkSelf && renderer != null && renderer.applied) {
				return true;
			}
			for (byte xi = 0; xi < CHILD_DIMENSION; ++xi) {
				for (byte yi = 0; yi < CHILD_DIMENSION; ++yi) {
					for (byte zi = 0; zi < CHILD_DIMENSION; ++zi) {
						if (children[xi, yi, zi].GetType() == typeof(VoxelBlock)) {
							if (!((VoxelBlock)children[xi, yi, zi]).filledWithSubRenderers(true))
								return false;
						} else
							return false;
					}
				}
			}
			return true;
		}

		private float getDistSquare(Vector3 otherPos, Vector3 myPos, float size) {
			return (otherPos - myPos * size).sqrMagnitude;
			//return Mathf.Max(Mathf.Max(Mathf.Abs(dif.x) - size * 0.5f, Mathf.Abs(dif.y) - size * 0.5f), Mathf.Abs(dif.z) - size * 0.5f);
		}

	}

}