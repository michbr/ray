
#ifndef DRACO_VOXEL_INDEX_H
#define DRACO_VOXEL_INDEX_H

#include "EXPORT.h"
#include "voxel.h"

#include <functional>
#include <iostream>


namespace Vox {

	class DRACO_VOXEL_API Index {
	public:
		unsigned int x, y, z;
		byte depth;

		Index();

		Index(byte depth);
		Index(byte depth, unsigned int x, unsigned int y, unsigned int z);
		Index(const Index &source);

		Index getChild() const;
		Index getChild(byte index) const;
		Index getNeighbor(byte index) const;
		Index getParent(byte depth) const;
		byte directionTo(const Index& child) const;

		bool operator==(const Index &o) const;
		int &operator[](int index);
		int operator[](int index) const;
	};
}

DRACO_VOXEL_API std::ostream& operator<<(std::ostream& out, const Vox::Index& index);


namespace std {
	template <> struct DRACO_VOXEL_API hash<Vox::Index> {
	public:
		size_t operator()(const Vox::Index& i) const;
	};
}

#endif //DRACO_VOXEL_INDEX_H