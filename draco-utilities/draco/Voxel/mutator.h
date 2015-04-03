
#ifndef DRACO_VOXEL_MUTATOR_H
#define DRACO_VOXEL_MUTATOR_H

#include "node.h"
#include "tree.h"
#include "voxel.h"


namespace Vox {
	class Mutator {
	public:
//		enum TAction {
//			traverse,
//			ignore,
//			replace
//		};

		virtual void apply(Tree& target) const;


	protected:
		virtual bool mutate(const Tree& target, const Index& pos, byte index, Node& parent) const = 0;
	    virtual void getBounds(const Tree& target, Index& min, Index& max) const = 0;
//		virtual bool traverse(const Index&) const = 0;

	private:
		void apply(Tree& target, Node& node, const Index& min, const Index& max, const Index&) const;
	};
}


#endif // DRACO_VOXEL_MUTATOR_H