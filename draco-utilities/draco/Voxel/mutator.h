
#ifndef DRACO_VOXEL_MUTATOR_H
#define DRACO_VOXEL_MUTATOR_H

#include "node.h"
#include "tree.h"
#include "voxel.h"
#include "index.h"


namespace Vox {
	class Mutator {
	public:
//		enum TAction {
//			traverse,
//			ignore,
//			replace
//		};

		void apply(Tree& target) const;


	protected:
		
		class Application {
		public:
			Index min, max;
			Tree* tree;
			
			Application();
		};
		
	    virtual Application* setup(Tree& target) const;
		virtual bool mutate(Application* app, const Index& pos, byte index, Node& parent) const = 0;
		virtual void breakdown(Application* app) const;
		

	private:
		void apply(Application* app, Node& node, const Index&) const;
	};
}


#endif // DRACO_VOXEL_MUTATOR_H