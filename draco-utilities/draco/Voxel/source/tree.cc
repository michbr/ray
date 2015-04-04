
#include "tree.h"

using namespace std;
using namespace Vox;


//////////////////
//  Tree class  //
//////////////////

Tree::Tree(byte maxDepth, double size): maxDepth(maxDepth), size(size), voxSize(size /(2 << maxDepth)), pos(0, 0, 0) {}


void Tree::addWorld(WorldModel* world) {
	worlds.push_back(world);
}
void Tree::removeWorld(WorldModel* world) {
	worlds.remove(world);
}
const std::list<WorldModel*>& Tree::getWorlds() const {
	return worlds;
}

