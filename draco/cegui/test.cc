

//#include "CEGUI.h"
#include "CEGUI/System.h"
#include "CEGUI/WindowManager.h"
#include "CEGUI/WindowFactoryManager.h"
#include "CEGUI/widgets/FrameWindow.h"
#include "CEGUI/Singleton.h"
#include "CEGUI/RendererModules/OpenGL/GLRenderer.h"

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
	
	//CEGUI::FrameWindow *frame = static_cast<CEGUI::FrameWindow*>(window.createWindow("TaharezLook/FrameWindow", "testWindow"));
	CEGUI::FrameWindow *frame = static_cast<CEGUI::FrameWindow*>(window.createWindow("DefaultWindow", "testWindow"));
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

