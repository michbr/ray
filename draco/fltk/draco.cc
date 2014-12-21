
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Tabs.H"

#include <iostream>


const unsigned int TAB_BUTTON_HEIGHT = 25;
const unsigned int DEFAULT_WINDOW_WIDTH = 800;
const unsigned int DEFAULT_WINDOW_HEIGHT = 600;
const char *DEFAULT_FLTK_SCHEME = "plastic";


using namespace std;

Fl_Group *addTab(Fl_Group *tabs, const char *label) {
	return new Fl_Group(0, TAB_BUTTON_HEIGHT, tabs->w(), tabs->h() -TAB_BUTTON_HEIGHT, label);
}

int main(int argc, char **argv) {

	Fl_Window *window = new Fl_Window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	{
		Fl_Tabs *tabs = new Fl_Tabs(2, 0, window->w() - 4, window->h() - 2);
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
			tab1->end();

			Fl_Group *tab2 = addTab(tabs, "another tab!");
			tab2->end();
		}
		tabs->end();
	}
	window->end();
	window->show(argc, argv);

	Fl::scheme(DEFAULT_FLTK_SCHEME);

	int endCode = Fl::run();

	return endCode;
}