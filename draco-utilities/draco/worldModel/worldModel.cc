#include "worldModel.h"
#include "renderer.h"

using namespace std;

WorldModel::WorldModel() {
	//vector<string> test;
	//getFiles(folder, test);
	//cout << test.size() << endl;
	//for (int i = 0; i < test.size(); i++) {
	//	cout << test[i] << endl;
	//}
}

void WorldModel::addObject(SceneObject * asset) {
	assets.insert(asset);
	for(BaseRenderer *rend: renderers) {
		rend->addObject(asset);
	}
}

void WorldModel::removeObject(SceneObject *asset) {
	assets.erase(asset);
}

vector<Face *> & WorldModel::getFaces() {
	//cout << "got here" << endl;
	//SceneObject * test = assets[0];
	//for (int i = 0; i < assets[0]->getFaces().size(); i++) {
	//	cout << i << endl;
	//}
	return (*assets.begin())->getFaces();
}

vector<Vector3<double>> WorldModel::getVertices() {
	vector<Vector3<double>> result;
	for(auto asset: assets) {
		vector<Face*> faces = asset->getFaces();
		for (int i = 0; i < faces.size(); i++) {
			vector<Vector3<double>> vertices = faces[i]->getVertices();
			for (int j = 0; j < vertices.size(); j++) {
				result.push_back(vertices[j]);
			}
		}
	}
	return result;
}

/*vector<Light *> WorldModel::getLights() {
	return assets[0].getFaces();
}*/

void WorldModel::addRenderer(BaseRenderer &rend) {
	renderers.push_back(&rend);
	for(SceneObject *ob: assets) {
		rend.addObject(ob);
	}
}

void WorldModel::removeRenderer(BaseRenderer &rend) {
	renderers.push_back(&rend);
	for(SceneObject *ob: assets) {
		rend.removeObject(ob);
	}
}
