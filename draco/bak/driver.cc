#include "dragonmath.h"
#include "worldModel.h"
#include "camera.h"
#include "wireframe.h"
#include "renderer.h"
#include "loader.h"

#include <iostream>
#include <sys/types.h>
#include <errno.h>
//#include <unistd.h>

using namespace std;

//std::unordered_map<std::string, bool> supportedTypes { {"obj", true} };

/*bool getFiles (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return false;
    }

    while ((dirp = readdir(dp)) != NULL) {
        string ending = string(dirp->d_name);
        size_t dotPos = ending.find_last_of(".");
        if (dotPos != string::npos && dotPos < (ending.length() -1)) {
                ending = ending.substr(dotPos+1);
                //cout << ending << endl;
                if (supportedTypes.count(ending)) {
                        files.push_back(dir + "/" + dirp->d_name);
                }
        }
    }
    closedir(dp);
    return true;
}*/



int main (int argc, char * argv [] ) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " " << "<SCENE_PATH> <OUTPUT_IMAGE>" << endl;
		exit(1);
	}
	WorldModel m = WorldModel();
	AssetLoader::loadAsset(argv[1], m);
/*	vector<string> test;
	if (chdir(argv[1]) < 0) {
		cerr << "Unable to access folder: " << argv[1] << endl;
		exit(1);
	}
	getFiles(".", test);
	for (int i = 0; i < test.size(); i++) {
//		cout << test[i] << endl;
		m.addObject(test[i]);
	}*/
	Vector3<double> pos = Vector3<double>(1, 1, 1);
	Vector3<double> normal = Vector3<double>(0, 0, 1);
	Vector3<double> up = Vector3<double>(0, 1, 0);
	
	Camera * cam = new Camera(string("primary"), pos, normal, up, 1.0);
	
	Wireframe * frame = new Wireframe("default", -256, -256, 256, 256, 1);
	Renderer r = Renderer(cam);
	r.set_frame(frame);
	
	vector<Light *> lights;
	lights.push_back(new Light(0, 0, 0, 0, 0,   0,   0));	
	lights.push_back(new Light(8, 8, 8, 1, 250, 250, 250));
	lights.push_back(new Light(2, 7, 6, 1, 250, 250, 250));
	//m.getFaces()
	
	/*cout << "what?" << endl;
	for (int i = 0; i < m.getFaces().size(); i++) {
		cout << i << endl;
	}*/
	r.prepareRaycast(m.getFaces(), lights);
	
	ofstream output;
	
	output.open(argv[2]);
	output << (r);
	output.close();
	
}