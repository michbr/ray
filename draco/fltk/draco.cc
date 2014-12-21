
#include "FL/Fl.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Tabs.H"

#include <iostream>


using namespace std;

int main(int argc, char **argv) {

	Fl_Window *window = new Fl_Window(640, 480);
	{
		Fl_Tabs *tabs = new Fl_Tabs(10, 10, 620, 440);
		{
			int x, y, w, h, tabH;
			tabs->client_area(x, y, w, h, tabH);
			Fl_Group *tab1 = new Fl_Group(5, 5, tabs->w() -10, tabs->h() -45, "Tab 1");
			{
				Fl_Box *box = new Fl_Box(20, 40, 260, 100, "Hello, World!");
				box->box(FL_UP_BOX);
				box->labelsize(36);
				box->labelfont(FL_BOLD + FL_ITALIC);
				box->labeltype(FL_SHADOW_LABEL);
			}
			tab1->end();
		}
		tabs->end();
	}
	window->end();
	window->show(argc, argv);

	Fl::scheme("plastic");

	int endCode = Fl::run();

	return endCode;
}