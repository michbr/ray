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
#include <FL/fl_draw.H>

#include <chrono>
#include <cstring>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <thread>

using namespace std;

static const int IMAGE_WIDTH = 256;
static const int IMAGE_HEIGHT = 256;

DRACO_SCALE_API Scale *constructScale(ScaleType *type, Fl_Group *pane, const string &file) {
	return new RayTracer(type, pane, file);
}

DRACO_SCALE_API const char *scaleName() {
	return TAB_NAME;
}

class ImageMonitor : public Runnable {
private:
	Renderer * render;
	Image * imageData;
	long lastValue = 0;
public:
	ImageMonitor(Renderer * r, Image * i) {
		render = r;
		imageData = i;
	}
	virtual void run() {
		while (true) {
       			 long current = render->getCurrentPixel();
       			 for (long i = lastValue; i < current; i++) {
        		        vector<int> * color = render->getPixelColor(i);
        		        int y = i/(render->getImageWidth());
        		        int x = i % (render->getImageWidth());
	                	(*imageData)(x, y).r( (uchar)((*color)[0]));
	                	(*imageData)(x, y).g( (uchar)((*color)[1]));
	                	(*imageData)(x, y).b( (uchar)((*color)[2]));
	        	}
	        	lastValue = current;
	        	this_thread::sleep_for(chrono::milliseconds(50));
	        }
	}
};

class DisplayMonitor : public Runnable {
private:
	ImageBox * box;
	Fl_Output * out;
	Renderer * render;
	string text;
public:
	DisplayMonitor(Renderer * r, ImageBox * b, Fl_Output * o) {
		render = r;
		box = b;
		out = o;
	}
	virtual void run() {
	        while(true) {
        	        long current = render->getCurrentPixel();
        	        double progress = (double)current/(double)(render->getImageHeight() * render->getImageWidth());
			text = "";
        		stringstream s;
        		s << setprecision(2) << (progress*100) << "%";
			s >> text;
        		Fl::awake((Fl_Awake_Handler)setText, this);
        		this_thread::sleep_for(chrono::milliseconds(200));
        	}
	}

	static void setText(void * test) {
		DisplayMonitor * instance = (DisplayMonitor*)test;
        	instance->out->value(instance->text.c_str());
        	instance->box->redraw();
	}

};

void RayTracer::handleButton( Fl_Widget* obj , void* caller) {
	RayTracer * instance = (RayTracer*)caller;
	if(!instance->started) {
		cout << "Starting ray trace..." << endl;
		instance->rayTracer = new Thread(instance);
		instance->rayTracer->start();
	/*	cout << "Starting UI polling..." << endl;
		instance->displayUpdater = new Thread(new DisplayMonitor(instance->renderer, instance->imageBox, instance->selectedFileDisplay));
		instance->displayUpdater->start();
	
		cout << "Starting image polling..." << endl;
		instance->imageUpdater = new Thread(new ImageMonitor(instance->renderer, instance->imageData));
		instance->imageUpdater->start();
*/
		instance->started = true;
	}
}


RayTracer::RayTracer(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	started = false;
	imageData = new Image(IMAGE_HEIGHT, IMAGE_WIDTH);
	Vector3<double> pos = Vector3<double>(1, 1, 1);
	Vector3<double> normal = Vector3<double>(0, 0, 1);
	Vector3<double> up = Vector3<double>(0, 1, 0);
	Camera * cam = new Camera(string("primary"), pos, normal, up, 1.0);

        Wireframe * frame = new Wireframe("default", -IMAGE_WIDTH/2, -IMAGE_HEIGHT/2, IMAGE_WIDTH/2, IMAGE_HEIGHT/2, 1);
        renderer = new Renderer(cam);
        renderer->set_frame(frame);
	lights = new vector<Light *>();
        lights->push_back(new Light(0, 0, 0, 0, 0,   0,   0));
        lights->push_back(new Light(8, 8, 8, 1, 250, 250, 250));
        lights->push_back(new Light(2, 7, 6, 1, 250, 250, 250));
	pane->current(pane);
	{
		selectedFileDisplay = new Fl_Output(10, 30, 150, 30, "");
		selectedFileDisplay->value("../../old/models/cube/");

		imageBox = new ImageBox(imageData->getRawImage(), 20, 70, IMAGE_WIDTH, IMAGE_HEIGHT);
		button = new Fl_Button(165, 30, 40, 30, "Go");		
		button -> callback( ( Fl_Callback* ) handleButton, this );
	}
}

void RayTracer::run () {
	string path (selectedFileDisplay->value());
	loadModel(path);	

        cout << "Starting UI polling..." << endl;
        displayUpdater = new Thread(new DisplayMonitor(renderer, imageBox, selectedFileDisplay));
        displayUpdater->start();

        cout << "Starting image polling..." << endl;
        imageUpdater = new Thread(new ImageMonitor(renderer, imageData));
        imageUpdater->start();

	renderer->prepareRaycast(model->getFaces(), *lights);
	cout << "Finished trace." << endl;
}

void RayTracer::loadModel(string location) {
        model = new WorldModel();
        AssetLoader::loadAsset(location.c_str(), *model);
}


RayTracer::~RayTracer() {
	free(pane);
}
