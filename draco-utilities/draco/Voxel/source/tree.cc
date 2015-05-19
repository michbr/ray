
#include "tree.h"

using namespace std;
using namespace Vox;


//////////////////
//  Tree class  //
//////////////////

Tree::Tree(byte maxDepth, double size): maxDepth(maxDepth), size(size), voxSize(size /(1 << maxDepth)), pos(0, 0, 0) {}


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

void Tree::pushDirtyMesh(Index mesh) {
	dirtyMeshes.push_back(mesh);
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

void Tree::setPolygonizer(Polygonizer* polygonizer) {
	this->polygonizer = polygonizer;
	polygonizer->setTree(this);
}
Polygonizer* Tree::getPolygonizer() {
	return polygonizer;
}

void Tree::updateMesh(const Index& i) {
	Mesh* m = meshes[i];
	if (m == NULL) {
		m = new Mesh(this);
		meshes[i] = m;
	}
	m->update(MeshIterator(this, i));
}
bool Tree::updateDirtyMesh() {
	if (dirtyMeshes.empty())
		return false;
	Index i = dirtyMeshes.front();
	dirtyMeshes.pop_front();
	updateMesh(i);
	return true;
}
void Tree::updateDirtyMeshes() {
	while(!dirtyMeshes.empty()) {
		Index i = dirtyMeshes.front();
		dirtyMeshes.pop_front();
		updateMesh(i);
	}
}
void Tree::updateAllMeshes() {
	Index i(maxDepth-Mesh::VOXEL_DEPTH, 0, 0, 0);
	int width = 1<<(maxDepth -Mesh::VOXEL_DEPTH);
	cout << "tree width: " << width << endl;
	for(i.x=0; i.x<width; ++i.x) {
		for(i.y=0; i.y<width; ++i.y) {
			for(i.z=0; i.z<width; ++i.z) {
				updateMesh(i);
			}
		}
	}
}
