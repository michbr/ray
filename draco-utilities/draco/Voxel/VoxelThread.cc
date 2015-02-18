using UnityEngine;
using System.Collections.Generic;
using System;
using System.Threading;
using System.Linq;

namespace Vox {

	[AddComponentMenu("Scripts/Voxel/VoxelThread")]
	[ExecuteInEditMode]
	public class VoxelThread : MonoBehaviour {

		private static bool initialized = false;
		private static Thread updateThread;
		private static Thread checkThread;
		private static BlockingQueue<VoxelJob> checkQueue;
		public static BlockingQueue<VoxelJob> updateQueue;

		//private static VoxelThread threader;
		private static bool running;

		//public static VoxelThread current {
		//	get {
		//		initialize();
		//		return threader;
		//	}
		//}

		public static void initialize() {
			if (initialized/* || threader != null*/)
				return;


			//quitting = false;
			//GameObject o = new GameObject("VoxelThreads");
			//o.hideFlags = HideFlags.HideAndDontSave | HideFlags.HideInHierarchy | HideFlags.HideInInspector;
			//threader = o.AddComponent<VoxelThread>();
			running = true;
			initialized = true;


			ThreadStart start;
			//ThreadStart start = new ThreadStart(checkThreadReader);
			//checkThread = new Thread(start);
			//checkThread.Start();
			updateQueue = new BlockingQueue<VoxelJob>();
			start = new ThreadStart(updateThreadReader);
			updateThread = new Thread(start);
			updateThread.Start();
			//updateCheckQueue = new Queue<VoxelUpdateJob>(200);
		}

		public static void enqueueUpdate(VoxelJob job) {
			initialize();
			updateQueue.enqueue(job);
			//MonoBehaviour.print("WHO's your daddy?");
		}

		//private static void checkThreadReader() {
		//	//while (true) {
		//		while (updateCheckQueue.Count > 0) {
		//			VoxelUpdateJob job = updateCheckQueue.Dequeue();
		//			//job.getBlock().updateAll(new VoxelUpdateInfo(job.getUpdateInfo(), (byte)job.xOff, (byte)job.yOff, (byte)job.zOff));
		//		}
		//	//}
		//}

		//private static void checkThreadReader() {
		//	while (running) {
		//		checkQueue.dequeue().execute();
		//	}
		//}

		private static void updateThreadReader() {
			while (running) {
				updateQueue.dequeue().execute();
			}
		}

		//public void OnApplicationQuit() {
		//	running = false;
		//	threader = null;
		//	initialized = false;
		//	updateThread.Interrupt();
		//	updateThread.Join();
		//}

		//void OnDestroy() {
		//	if (threader == this) {
		//		threader = null;
		//	}
		//}

	}


	[ExecuteInEditMode]
	public class BlockingQueue<Type> {

		private Queue<Type> queue;
		private Semaphore sem;

		public int count { get { return queue.Count; } }

		public BlockingQueue() {
			queue = new Queue<Type>();
			sem = new Semaphore(0, int.MaxValue);
		}

		public void enqueue(Type item) {
			lock (queue) {
				queue.Enqueue(item);
			}
			sem.Release();
		}

		public Type dequeue() {
			sem.WaitOne();
			lock (queue) {
				return queue.Dequeue();
			}
		}
	}

}