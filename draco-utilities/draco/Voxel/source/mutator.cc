
#include "mutator.h"
#include "index.h"

using namespace std;
using namespace Vox;


void Mutator::apply(Tree& target) const {
	Application* app = setup(target);
//	cout << "min: " << min << endl;
//	cout << "max: " << max << endl;
	apply(app, target.head, Index(0));
}

void Mutator::apply(Application* app, Node& node, const Index& pos) const {
	Index cornerChild = pos.getChild();
	for(byte c=0; c <Node::CHILD_COUNT; ++c) {
		Index childPos = cornerChild.getNeighbor(c);
		bool traverse = mutate(app, childPos, c, node);
		if (traverse && pos.depth < app->tree->maxDepth)
			apply(app, node.expand(c), childPos);
	}
}


Mutator::Application* Mutator::setup(Tree& target) const {
	Mutator::Application* app = new Mutator::Application();
	unsigned int width = (1 << (target.maxDepth)) -1;
	app->tree = &target;
	app->min = Index(target.maxDepth);
	app->max = Index(target.maxDepth, width, width, width);
	return app;
}

//void* Mutator::setup(Tree& target) const {
//	return NULL;
//}

void Mutator::breakdown(Application* app) const {
	delete app;
}

Mutator::Application::Application() {
	
}