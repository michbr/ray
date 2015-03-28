
#include "../mutator.h"

using namespace std;
using namespace Vox;


void Mutator::apply(Tree& target) const {
	apply(target.head, Index());
}

void Mutator::apply(Node& target, const Index& p) const {
	Index cp = p.getChild();
	for(int i=0; i<target.CHILD_COUNT; ++i) {
		if (this->action(p))
			;
	}
}