#include "worldModel.h"

#include <vector>
#include <iostream>

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
	assets.push_back(asset);
//	SceneObject * head = new SceneObject();
//	AssetLoader::loadAsset(filename, *head);
//	assets.push_back(head);
/*	vector<string> blah = head->getTextures();
	char * cwd = new char[255];
	getcwd(cwd, 255);
	for (int i = 0; i < blah.size(); i++)  {
		string texPath = "";
		texPath.append(cwd);
		texPath.append("/");
		texPath.append(blah[i]);

		cout << "Adding texture: " << texPath << endl;
		textures.push_back(TextureLoader::loadTexture(texPath));
				
	}*/
}

vector<Face *> & WorldModel::getFaces() {
	//cout << "got here" << endl;
	//SceneObject * test = assets[0];
	//for (int i = 0; i < assets[0]->getFaces().size(); i++) {
	//	cout << i << endl;
	//}
	return assets[0]->getFaces();
}

/*vector<Light *> WorldModel::getLights() {
	return assets[0].getFaces();
}*/
