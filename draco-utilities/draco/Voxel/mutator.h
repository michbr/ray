//
// Created by Cullen on 3/26/2015.
//

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

		void apply(Tree &target) const;

		virtual Voxel mutate(const Index&) const = 0;
		virtual TAction action(const Index&) const = 0;

	protected:

	};
}


#endif // DRACO_VOXEL_MUTATOR_H