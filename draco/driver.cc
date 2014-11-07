#include "dragonmath.h"
#include "worldModel.h"
#include "camera.h"
#include "wireframe.h"
#include "elipse.h"
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
	Vector3<double> * normal = new Vector3<double>();
	Vector3<double> * up = new Vector3<double>();
	
	(*normal)[0] = (.25);
	(*normal)[1] = (1);
	(*normal)[2] = (1);
	
	(*up)[0] = (0);
	(*up)[1] = (1);
	(*up)[2] = (0);
	
	Camera * cam = new Camera("primary", 1, 2, 7, 6, normal, up);
	
	
	
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
	for (int i = 0; i < lights.size(); i++) {
		cout << (*(lights[i]->get_color()))[0] << ", ";
		cout << (*(lights[i]->get_color()))[1] << ", ";
		cout << (*(lights[i]->get_color()))[2] << endl;
	}
	
	r.prepare_raycast(m.getFaces(), vector<Elipse *>(), lights);
	
	ofstream output;
	
	output.open(argv[2]);
	output << (r);
	output.close();
	
}
