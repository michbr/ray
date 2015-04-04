#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "node.h"
#include "voxel.h"
#include "mesh.h"

#include <worldModel/worldModel.h>


namespace Vox {

	class Mesh;


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

	protected:
//		std::unordered_map<Index, Mesh> meshes;
		std::list<WorldModel *> worlds;
    };

}


#endif //DRACO_VOX_TREE_H