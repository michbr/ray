
#include "mutator.h"

using namespace std;
using namespace Vox;


void Mutator::apply(Tree& target) const {
	Index min, max;
	getBounds(target, min, max);
	apply(target, target.head, min, max, Index());
}

void Mutator::apply(Tree& target, Node& node, const Index& min, const Index& max, const Index& pos) const {
	Index cornerChild = pos.getChild();
	for(int c=0; c <node.CHILD_COUNT; ++c) {
		Index childPos = cornerChild.getNeighbor(c);
		bool traverse = mutate(target, childPos, c, node);
		if (traverse && pos.depth < target.maxDepth)
			apply(target, node.getNode(c), min, max, childPos);
	}
}