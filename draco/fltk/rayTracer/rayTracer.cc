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

thread *test;

class GUIUpdate {
private:	
	string text;
	Fl_Output * textField;
	ImageBox * box;
public:
	GUIUpdate(ImageBox * imageView, Fl_Output * view, string contents) {
		text = contents;
		textField = view;
		box = imageView;
	}

	ImageBox * getImageBox() {
		return box;
	}

	Fl_Output * getField() {
		return textField;
	}

	string getText() {
		return text;
	}
};

void doRayTrace(WorldModel * model, Renderer * renderer, vector<Light *> * lights) {
        renderer->prepareRaycast(model->getFaces(), *lights);
        cout << "Finished trace." << endl;
}

void setText(void * update) {
	GUIUpdate* updater = (GUIUpdate*)update;
	updater->getField()->value(updater->getText().c_str());
	updater->getImageBox()->redraw();
}

long lastValue = 0;

void updateImage(Renderer * render, Image * imageData) {
	while (true) {
	long current = render->getCurrentPixel();
	for (long i = lastValue; i < current; i++) {
		vector<int> * color = render->getPixelColor(i);
		int y = i/(render->getImageWidth());
		int x = i % (render->getImageWidth());
	//	cout << static_cast<int>((uchar)((*color)[0])) << ", " << static_cast<int>((uchar)((*color)[1]))
	//		<< ", " << static_cast<int>((uchar)((*color)[2])) << endl;
		(*imageData)(x, y).r( (uchar)((*color)[0]));
		(*imageData)(x, y).g( (uchar)((*color)[1]));
		(*imageData)(x, y).b( (uchar)((*color)[2]));
	}
	lastValue = current;
	this_thread::sleep_for(chrono::milliseconds(100));
	}

}

void updateUI(ImageBox * box, Fl_Output * out, Renderer * render) {
	while(true) {
		long current = render->getCurrentPixel();
		double progress = (double)current/(double)(render->getImageHeight() * render->getImageWidth());
		stringstream s;
		s << setprecision(2) << (progress*100) << "%";
		if ( current > lastValue) {
			Fl::awake((Fl_Awake_Handler)setText, new GUIUpdate(box, out, s.str()));
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}	
}

thread * getImageData;
void RayTracer::handleButton( Fl_Widget* obj , void* caller) {
	RayTracer * instance = (RayTracer*)caller;
	string path (instance->selectedFileDisplay->value());
	instance->loadModel(path);
	cout << "Starting ray trace..." << endl;
	instance->runner = new thread(doRayTrace, instance->model, instance->renderer, instance->lights);
	cout << "Starting UI polling..." << endl;
	test = new thread(updateUI, instance->imageBox, instance->selectedFileDisplay, instance->renderer);
	cout << "Starting image polling..." << endl;
	getImageData = new thread(updateImage, instance->renderer, instance->imageData);
}


RayTracer::RayTracer(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	imageData = new Image(IMAGE_HEIGHT, IMAGE_WIDTH);
	Vector3<double> pos = Vector3<double>(1, 1, 1);
	Vector3<double> normal = Vector3<double>(0, 0, 1);
	Vector3<double> up = Vector3<double>(0, 1, 0);
	Camera * cam = new Camera(string("primary"), pos, normal, up, 1.0);
//	image = new uchar[2048][2048][3];

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
		selectedFileDisplay->value("../../cube/");

		//fl_draw_image((const uchar*)&image, 20, 50, 1024, 1024, 3, 0);
		imageBox = new ImageBox(imageData->getRawImage(), 20, 70, IMAGE_WIDTH, IMAGE_HEIGHT);
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
