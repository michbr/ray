#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "index.h"
#include "mesh.h"
#include "node.h"
#include "polygonizer.h"
#include "voxel.h"

#include <worldModel/worldModel.h>
#include <unordered_map>


namespace Vox {

//	class Mesh;


    class Tree {
    public:
		const byte maxDepth;
		const double size, voxSize;
		Vector3<double> pos;
		Node head;

		Tree(byte maxDepth, double size);

		void addWorld(WorldModel* world);
		void removeWorld(WorldModel* world);
		const std::list<WorldModel*>& getWorlds() const;

		void pushMesh(SceneObject* mesh) const;
		void removeMesh(SceneObject* mesh) const;

		void setPolygonizer(Polygonizer<double> *);
		Polygonizer<double>* getPolygonizer();
		
		void updateMeshes();

	protected:
		std::unordered_map<Index, Mesh> meshes;
		std::list<WorldModel *> worlds;
		Polygonizer<double>* polygonizer;

		void pushMeshes(WorldModel* world) const;
		void clearMeshes(WorldModel* world) const;
    };

}


#endif //DRACO_VOX_TREE_H