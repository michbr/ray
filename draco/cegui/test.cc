

//#include "CEGUI.h"
#include "CEGUI/System.h"
#include "CEGUI/WindowManager.h"
#include "CEGUI/WindowFactoryManager.h"
#include "CEGUI/widgets/FrameWindow.h"

#include <iostream>


using namespace std;
using namespace CEGUI;

int main(int argc, char **argv) {
	
	cout << "HI!" << endl;
	
//	WindowManager *window = &Singleton<WindowManager>::getSingleton();
//	WindowFactoryManager *factoryM = &Singleton<WindowFactoryManager>::getSingleton();
//	WindowFactory *factory = factoryM->getFactory("DefaultWindow");
	WindowManager &window = WindowManager::getSingleton();
	Window *root = window.createWindow("DefaultWindow", "root");
	System::getSingleton().getDefaultGUIContext().setRootWindow(root);
	
	FrameWindow *frame = static_cast<FrameWindow*>(window.createWindow("TaharezLook/FrameWindow", "testWindow"));
	root->addChild(frame);
	
	frame->setPosition(UVector2(UDim(0.25f, 0), UDim(0.25f, 0)));
	frame->setSize(USize(UDim(0.5f, 0), UDim(0.5f, 0)));
	
	frame->setText("Hello World!");
	
	return 0;
}

