
#ifndef DRACO_VOXEL_MUTATOR_H
#define DRACO_VOXEL_MUTATOR_H

#include "EXPORT.h"
#include "index.h"
#include "node.h"
#include "tree.h"
#include "voxel.h"


namespace Vox {

	class DRACO_VOXEL_API Mutator {
	public:
		virtual void apply(Tree& target) const;

	protected:
		struct Action {
			bool traverse;
			bool modified;
			Action(bool traverse, bool modified);
		};
		
		struct Application {
			Index min, max;
			Tree* tree;
		};
		
	    virtual Application* setup(Tree& target) const;
		virtual Action mutate(Application* app, const Index& pos, byte index, Node& parent) const = 0;
		virtual void breakdown(Application* app) const;
		

	private:
		void apply(Application* app, Node& node, const Index&) const;
	};
}


#endif // DRACO_VOXEL_MUTATOR_H