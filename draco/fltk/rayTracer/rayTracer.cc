
#include "rayTracer.h"
#include "loader.h"
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
	((RayTracer*)caller)->loadModel("../cube/");
//   obj->label( "OFF" ); 
   
//   obj->resize( 0,0,40,40 ); 
  // obj->redraw();
}


RayTracer::RayTracer(ScaleType *type, Fl_Group *pane, const string &startDir): Scale(type, pane, startDir) {
	pane->current(pane);
	{
		Fl_Output * selectedFileDisplay = new Fl_Output(10, 30, 150, 30, "");
		selectedFileDisplay->value("../cube/");
		Fl_Button * button = new Fl_Button(165, 30, 60, 30, "Button");		
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
