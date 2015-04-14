
#ifndef DRACO_VOXEL_INDEX_H
#define DRACO_VOXEL_INDEX_H

#include "voxel.h"
#include <functional>


namespace Vox {
	class Index {
	public:
		int x, y, z;
		unsigned char depth;

		Index();

		Index(unsigned char depth);
		Index(unsigned char depth, int x, int y, int z);
		Index(const Index &source);

		Index getChild() const;
		Index getChild(unsigned char index) const;
		Index getNeighbor(unsigned char index) const;
		Index getParent(unsigned char depth) const;
		byte directionTo(const Index& child) const;

		bool operator==(const Index &o) const;
		int &operator[](int index);
		int operator[](int index) const;
	};
}



namespace std {
	template <> struct hash<Vox::Index> {
	public:
		size_t operator()(const Vox::Index& i) const;
	};
}

#endif //DRACO_VOXEL_INDEX_H