

// necessary to allow loading of plugins (otherwise compiles as exporter)
#ifdef _WIN32
//	#define NTDDI_VERSION NTDDI_WINXP
	#define _WIN32_WINNT _WIN32_WINNT_WS03
	#include <windows.h>
#endif // _WIN32

#include "util/path.h"
#include "scaleManager.h"
#include "FL/Fl_Widget.H"
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Tabs.H"

#include "util/directoryViewer.h"

#include <iostream>




const char *UTILITY_LIB_PATH = "\\..\\utilities\\lib";

const unsigned int TAB_BUTTON_HEIGHT = 25;
const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
const char *DEFAULT_FLTK_SCHEME = "plastic";


using namespace std;

void addLibDirectories() {
#ifdef _WIN32
	char path[MAX_EXECUTABLE_PATH_LENGTH];
	memset(path, 0, MAX_EXECUTABLE_PATH_LENGTH);
	int length = GetModuleFileName(NULL, path, MAX_EXECUTABLE_PATH_LENGTH);
	if (length >= MAX_EXECUTABLE_PATH_LENGTH)
		throw string("Path to executable too long: ") + path + " ...";
	if (length < 1)
		throw string("Could not get executable path");
	string fullPath(path);
	fullPath.erase(fullPath.find_last_of('\\'));
	fullPath += UTILITY_LIB_PATH;
	if (!SetDllDirectory(fullPath.c_str()))
		cout << "ERROR: " << GetLastError() << endl;
#endif
}

Fl_Group *addTab(Fl_Group *tabs, const char *label) {
	Fl_Group *g = new Fl_Group(tabs->x(), tabs->y() +TAB_BUTTON_HEIGHT, tabs->w(), tabs->h() -TAB_BUTTON_HEIGHT, label);
	Fl_Group *group = new Fl_Group(g->x() +2, g->y() +2, g->w() -4, g->h() -4, "");
	group->clip_children(true);
	return group;
}

int main(int argc, char **argv) {
	addLibDirectories();
	cout << "DIRECTORY: " << Path::exeDir().super() << endl;
	Fl::scheme(DEFAULT_FLTK_SCHEME);

	Fl_Window *window = new Fl_Window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	Fl_Tabs *tabs = new Fl_Tabs(2, 0, window->w() - 4, window->h() - 2);
	{
		window->add_resizable(*tabs);
		{
			//int x, y, w, h, tabH;
			//tabs->client_area(x, y, w, h, tabH);
			Fl_Group *tab1 = addTab(tabs, "test tab 1");
			tabs->resizable(*tab1);
			{
				Fl_Box *box = new Fl_Box(20, 40, 260, 100, "Hello, World!");
				box->box(FL_DOWN_FRAME);
				box->labelsize(36);
				box->labelfont(FL_BOLD + FL_ITALIC);
				box->labeltype(FL_SHADOW_LABEL);
			}
			tabs->current(tabs);

			Fl_Group *tab2 = addTab(tabs, "another tab!");
			{
				Fl_Box *box = new Fl_Box(10, 0, 200, 200, "howdy!");
				box->box(FL_DOWN_FRAME);
			}
			tabs->current(tabs);
		}
		tabs->end();
	}
	window->end();
	window->show(argc, argv);
	
	ScaleManager scaleMan;
	scaleMan.loadScaleList();
	vector<ScaleType> &scales = scaleMan.getScales();
	cout << "DIRECTORY: " << Path::exeDir().super() << endl;
	for(ScaleType &scale: scales) {
		try {
			scale.load();
		} catch (string s) {
			cerr << s << endl;
			continue;
		}
		tabs->current(tabs);
		Fl_Group *pane = addTab(tabs, scale.name.c_str());
	//	tabs->add(pane);
		cout << "DIRECTORY: " << Path::exeDir().super() << endl;
		scale.construct(pane, Path::exeDir().super());
	}
	cout << "GOT HERE!" << endl;
	int endCode = Fl::run();

	return endCode;
}
