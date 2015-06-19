#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "EXPORT.h"
#include "index.h"
#include "mesh.h"
#include "node.h"
#include "polygonizer.h"
#include "voxel.h"

#include <worldModel/worldModel.h>
#include <unordered_map>


namespace Vox {

//	class Mesh;
	class Polygonizer;


	class DRACO_VOXEL_API Tree {
    public:
		const byte maxDepth;
		const double size, voxSize;
		Vector3<double> pos;
		Node head;

		Tree(byte maxDepth, double size);

		void addWorld(WorldModel* world);
		void removeWorld(WorldModel* world);
		virtual const std::list<WorldModel*>& getWorlds() const;

		void pushDirtyMesh(Index mesh);
		void pushMesh(SceneObject* mesh) const;
		void removeMesh(SceneObject* mesh) const;

		void setPolygonizer(Polygonizer *);
		Polygonizer* getPolygonizer();

		void updateMesh(const Index& i);
		bool updateDirtyMesh();
		virtual void updateDirtyMeshes();
		virtual void updateAllMeshes();

	protected:
		std::unordered_map<Index, Mesh*> meshes;
		std::list<Index> dirtyMeshQueue;
		std::unordered_set<Index> dirtyMeshSet;
		std::list<WorldModel *> worlds;
		Polygonizer* polygonizer;

		void pushMeshes(WorldModel* world) const;
		void clearMeshes(WorldModel* world) const;
    };

}


#endif //DRACO_VOX_TREE_H