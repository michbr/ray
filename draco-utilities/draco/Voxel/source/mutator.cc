
#include "mutator.h"
#include "index.h"

using namespace std;
using namespace Vox;


void Mutator::apply(Tree& target) const {
	Application* app = setup(target);
	apply(app, target.head, Index(0));
}

void Mutator::apply(Application* app, Node& node, const Index& pos) const {
	Index cornerChild = pos.getChild();
	for(byte c=0; c <Node::CHILD_COUNT; ++c) {
		Index childPos = cornerChild.getNeighbor(c);
		Action a = mutate(app, childPos, c, node);
		if (childPos.depth == app->tree->maxDepth -Mesh::VOXEL_DEPTH && (a.modified || a.traverse))
			app->tree->pushDirtyMesh(childPos);
		if (a.traverse && pos.depth < app->tree->maxDepth)
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

void Mutator::breakdown(Application* app) const {
	delete app;
}

Mutator::Action::Action(bool traverse, bool modified): traverse(traverse), modified(modified) {}