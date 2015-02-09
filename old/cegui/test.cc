

//#include "CEGUI.h"
#include "CEGUI/System.h"
#include "CEGUI/WindowManager.h"
#include "CEGUI/WindowFactoryManager.h"
#include "CEGUI/SchemeManager.h"
#include "CEGUI/widgets/FrameWindow.h"
#include "CEGUI/Singleton.h"
#include "CEGUI/Scheme.h"
#include "CEGUI/Font.h"
#include "CEGUI/ImageManager.h"
#include "CEGUI/falagard/WidgetLookManager.h"
#include "CEGUI/XMLParser.h"
#include "CEGUI/RendererModules/OpenGL/GLRenderer.h"
#include "CEGUI/DefaultResourceProvider.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

#include <iostream>


using namespace std;


Display *dpy;
Window win;
XEvent xev;
XWindowAttributes gwa;

void startGLWindow() {
        Window main;
//        Display                 *dpy;
        GLint                   att[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        XVisualInfo             *vi;
        Colormap                cmap;
        XSetWindowAttributes    swa;
//        Window                  win;
        GLXContext              glc;
//        XWindowAttributes       gwa;
//        XEvent                  xev;
        dpy = XOpenDisplay(NULL);
        if(dpy == NULL) {
                cout << "\n\tcannot connect to X server\n" << endl;
                exit(0);
        }
        main = DefaultRootWindow(dpy);

        vi = glXChooseVisual(dpy, 0, att);

        if(vi == NULL) {
                cout << "\n\tno appropriate visual found\n" << endl;
                exit(0);
        }

        cmap = XCreateColormap(dpy, main, vi->visual, AllocNone);

        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | PointerMotionMask;

        win = XCreateWindow(dpy, main, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "Dragon");
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);

        glEnable(GL_DEPTH_TEST);
}


int main(int argc, char **argv) {
	
	cout << "HI!" << endl;
	startGLWindow();
	CEGUI::OpenGLRenderer &renderer = CEGUI::OpenGLRenderer::bootstrapSystem();
	cout << "bootstrapped?" << endl;
	CEGUI::WindowManager &window = CEGUI::WindowManager::getSingleton();
	cout << "CONSTRUCTED!" << endl;
	CEGUI::Window *root = window.createWindow("DefaultWindow", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
	
	// initialize the required directories for the DefaultResourceProvider
	CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("schemes", "../cegui-0.8.3/datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "../cegui-0.8.3/datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "../cegui-0.8.3/datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "../cegui-0.8.3/datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "../cegui-0.8.3/datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "../cegui-0.8.3/datafiles/lua_scripts/");

	// set the default resource groups to be used
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
//	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
//	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	// setup default group for validation schemas
	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
	CEGUI::FrameWindow *frame = static_cast<CEGUI::FrameWindow*>(window.createWindow("Vanilla/FrameWindow", "testWindow"));
	//CEGUI::FrameWindow *frame = static_cast<CEGUI::FrameWindow*>(window.createWindow("DefaultWindow", "testWindow"));
	root->addChild(frame);
	
	frame->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.25f, 0)));
	frame->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
	
	frame->setText("Hello World!");



        while(1) {
                XNextEvent(dpy, &xev);

                if(xev.type == Expose) {
                        XGetWindowAttributes(dpy, win, &gwa);
                        glViewport(0, 0, gwa.width, gwa.height);
                }
		CEGUI::System::getSingleton().renderAllGUIContexts();
		
                glXSwapBuffers(dpy, win);
		CEGUI::System::getSingleton().renderAllGUIContexts();
        }



	return 0;
}

