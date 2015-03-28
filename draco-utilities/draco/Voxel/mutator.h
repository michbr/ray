
#ifndef DRACO_VOXEL_MUTATOR_H
#define DRACO_VOXEL_MUTATOR_H

#include "node.h"
#include "tree.h"
#include "voxel.h"


namespace Vox {
	class Mutator {
	public:
		enum TAction {
			traverse,
			ignore,
			replace
		};

		void apply(Tree& target) const;


	protected:
		virtual Voxel mutate(const Index&) const = 0;
		virtual TAction action(const Index&) const = 0;

	private:
		void apply(Node& target, const Index&) const;
	};
}


#endif // DRACO_VOXEL_MUTATOR_H