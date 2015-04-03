#ifndef DRACO_VOX_TREE_H
#define DRACO_VOX_TREE_H

#include "node.h"
#include "voxel.h"
#include "mesh.h"

#include <unordered_map>
#include <worldModel/worldModel.h>

#include <DragonMath/vector.h>


namespace Vox {

	class Index;
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
		std::unordered_map<Index, Mesh> meshes;
		std::list<WorldModel *> worlds;
    };


	class Index {
	public:
		byte depth;
		int x, y, z;

		Index();
		Index(byte depth);
		Index(byte depth, int x, int y, int z);
		Index(const Index& source);

		Index getChild() const;
		Index getChild(byte index) const;
		Index getNeighbor(byte index) const;
		Index getParent(byte depth) const;

		bool operator==(const Index& o) const;
	};
}

namespace std {
	template <> struct hash<Vox::Index> {
	public:
		size_t operator()(const Vox::Index& i) const;
	};
}


#endif //DRACO_VOX_TREE_H
