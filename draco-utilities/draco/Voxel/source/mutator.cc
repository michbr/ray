
#include "mutator.h"

using namespace std;
using namespace Vox;


void Mutator::apply(Tree& target) const {
	apply(target, target.head, Index());
}

void Mutator::apply(Tree& target, Node& node, const Index& pos) const {
	Index childPos = pos.getChild();
	for(int c=0; c <node.CHILD_COUNT; ++c) {
		switch(action(pos)) {
			case ignore:
				break;
			case traverse:
				if (pos.depth < target.maxDepth) {
					apply(target, node.getNode(c), childPos.getNeighbor(c));
					break;
				}
			case replace:
				node.set(c, mutate(childPos.getNeighbor(c), node.get(c)));
				break;
		}
	}
}