
#include "rayTracer.h"
#include "loader.h"
#include "camera.h"
#include "wireframe.h"
#include "renderer.h"
#include "FL/Fl_File_Chooser.H"
#include "FL/Fl_Box.H"
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

#include <cstring>
#include <string>
#include <iostream>


using namespace std;

DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new RayTracer(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
	return TAB_NAME;
}

void RayTracer::handleButton( Fl_Widget* obj , void* caller) {
	RayTracer * instance = (RayTracer*)caller;
	string path (instance->selectedFileDisplay->value());
	instance->loadModel(path);

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
        r.prepareRaycast(instance->model->getFaces(), lights);
        ofstream output;

        output.open("out.ppm");
        output << (r);
        output.close();

}


RayTracer::RayTracer(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	{
		selectedFileDisplay = new Fl_Output(10, 30, 150, 30, "");
		selectedFileDisplay->value("../../cube/");
		button = new Fl_Button(165, 30, 40, 30, "Go");		
		button -> callback( ( Fl_Callback* ) handleButton, this );
	}
}

void RayTracer::loadModel(string location) {
        model = new WorldModel();
        AssetLoader::loadAsset(location.c_str(), *model);
}


RayTracer::~RayTracer() {
	free(pane);
}
