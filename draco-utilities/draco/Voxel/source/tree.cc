
#include "tree.h"

using namespace std;
using namespace Vox;


//////////////////
//  Tree class  //
//////////////////

Tree::Tree(byte maxDepth, double size): maxDepth(maxDepth), size(size), voxSize(size /(2 << maxDepth)), pos(0, 0, 0) {}


void Tree::addWorld(WorldModel* world) {
	pushMeshes(world);
	worlds.push_back(world);
}
void Tree::removeWorld(WorldModel* world) {
	clearMeshes(world);
	worlds.remove(world);
}
const std::list<WorldModel*>& Tree::getWorlds() const {
	return worlds;
}

void Tree::pushMeshes(WorldModel* world) const {
	for(auto mesh: meshes) {
		world->addObject(mesh.second->getObject());
	}
}
void Tree::clearMeshes(WorldModel *world) const {
	for(auto mesh: meshes) {
		world->removeObject(mesh.second->getObject());
	}
}

void Tree::pushMesh(SceneObject *mesh) const {
	for(auto world: worlds) {
		world->addObject(mesh);
	}
}
void Tree::removeMesh(SceneObject *mesh) const {
	for(auto world: worlds) {
		world->removeObject(mesh);
	}
}

void Tree::setPolygonizer(Polygonizer<double>* polygonizer) {
	this->polygonizer = polygonizer;
}
Polygonizer<double>* Tree::getPolygonizer() {
	this->polygonizer = polygonizer;
}

void Tree::updateMeshes() {
	Index i(maxDepth-Mesh::VOXEL_DEPTH, 0, 0, 0);
	int width = 1<<(maxDepth -Mesh::VOXEL_DEPTH);
	for(; i.x<width;++i.x) {
		for(; i.y<width;++i.y) {
			for(; i.z<width;++i.z) {
				Mesh* m = meshes[i];
                if (m == NULL)
                    meshes[i] = new Mesh(this);
                m->update(MeshIterator(this, i));
			}
		}
	}
}
