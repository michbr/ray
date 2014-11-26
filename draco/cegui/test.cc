

//#include "CEGUI.h"
#include "CEGUI/System.h"

#include <iostream>


using namespace std;
using namespace CEGUI;

int main(int argc, char **argv) {
	
	cout << "HI!" << endl;
	
	WindowManager &window = Singleton<WindowManager>::getSingleton();
//	WindowManager &window = WindowManager::getSingleton();
	Window *root = window.createWindow("DefaultWindow", "root");
	System::getSingleton().setGUISheet(root);
	
	FrameWindow *frame = (FrameWindow *)window.createWindow("TaharezLook/FrameWindow", "testWindow");
	root->addChildWindow(frame);
	
	frame->setPosition(UVector2(UDim(0.25f, 0), UDIM(0.25f, 0)));
	frame->setSize(UVector2(UDim(0.5f, 0), UDIM(0.5f, 0)))
	
	frame->setTest("Hello World!");
	
	return 0;
}

