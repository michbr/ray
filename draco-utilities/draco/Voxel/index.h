
#ifndef DRACO_VOXEL_INDEX_H
#define DRACO_VOXEL_INDEX_H

#include <functional>


namespace Vox {
	class Index {
	public:
		unsigned char depth;
		int x, y, z;

		Index();

		Index(unsigned char depth);
		Index(unsigned char depth, int x, int y, int z);
		Index(const Index &source);

		Index getChild() const;
		Index getChild(unsigned char index) const;
		Index getNeighbor(unsigned char index) const;
		Index getParent(unsigned char depth) const;

		bool operator==(const Index &o) const;
	};
}



namespace std {
	template <> struct hash<Vox::Index> {
	public:
		size_t operator()(const Vox::Index& i) const;
	};
}

#endif //DRACO_VOXEL_INDEX_H