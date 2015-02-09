#include "dragon.h"

#include "worldModel.h"
#include "camera.h"
#include "renderer.h"
#include "loader.h"

#include <iostream>
#include <cstdlib>

#if defined(__linux__)
#include <X11/Xlib.h>
#include <GL/glx.h>


using namespace std;

//int main( int argc, const char* argv[] ) {

/*	Window main;
	Display                 *dpy;
	GLint                   att[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo             *vi;
	Colormap                cmap;
	XSetWindowAttributes    swa;
	Window                  win;
	GLXContext              glc;
	XWindowAttributes       gwa;
	XEvent                  xev;
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
	
	DragonEngine engine = DragonEngine();
	engine.initWindow(600, 600);
	engine.placeCamera (
						0, 0, 8.,
						0, 0, 0,
						0., 1., 0.
						);
	//engine.initRenderer();
	
	while(1) {
		XNextEvent(dpy, &xev);

		if(xev.type == Expose) {
			XGetWindowAttributes(dpy, win, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);
			//drawQuad();

		}

		else if(xev.type == KeyPress) {
			engine.event(((XKeyEvent*)&xev)->keycode);
			//glXMakeCurrent(dpy, None, NULL);
			//glXDestroyContext(dpy, glc);
			//XDestroyWindow(dpy, win);
			//XCloseDisplay(dpy);
			//exit(0);
		}
		else if (xev.type == MotionNotify) {
			XMotionEvent * ev = (XMotionEvent*)&xev;
			engine.motionEvent(ev->x, ev->y);
		}
		engine.render();
		glXSwapBuffers(dpy, win);
	} /* this closes while(1) { */
//	startGLWindow();
//}

void startGLWindow() {
	Window main;
        Display                 *dpy;
        GLint                   att[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        XVisualInfo             *vi;
        Colormap                cmap;
        XSetWindowAttributes    swa;
        Window                  win;
        GLXContext              glc;
        XWindowAttributes       gwa;
        XEvent                  xev;
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

        DragonEngine engine = DragonEngine();
        engine.initWindow(600, 600);
        engine.placeCamera (
                                                0, 0, 8.,
                                                0, 0, 0,
                                                0., 1., 0.
                                                );
        //engine.initRenderer();

        while(1) {
                XNextEvent(dpy, &xev);

                if(xev.type == Expose) {
                        XGetWindowAttributes(dpy, win, &gwa);
                        glViewport(0, 0, gwa.width, gwa.height);
                        //drawQuad();

                }
                else if(xev.type == KeyPress) {
                        engine.event(((XKeyEvent*)&xev)->keycode);
                        //glXMakeCurrent(dpy, None, NULL);
                        //glXDestroyContext(dpy, glc);
                        //XDestroyWindow(dpy, win);
                        //XCloseDisplay(dpy);
                        //exit(0);
                }
                else if (xev.type == MotionNotify) {
                        XMotionEvent * ev = (XMotionEvent*)&xev;
                        engine.motionEvent(ev->x, ev->y);
                }
                engine.render();
                glXSwapBuffers(dpy, win);
        } /* this closes while(1) { */
}

int main( int argc, const char* argv[] ) {
	if (argc == 1) {
		cout << "No arguments; starting GL window." << endl;
		startGLWindow();
		exit(0);
	}
        else if (argc != 3) {
                cerr << "Usage: " << argv[0] << " " << "<SCENE_PATH> <OUTPUT_IMAGE>" << endl;
                exit(1);
        }
        WorldModel m = WorldModel();
        AssetLoader::loadAsset(argv[1], m);
/*      vector<string> test;
        if (chdir(argv[1]) < 0) {
                cerr << "Unable to access folder: " << argv[1] << endl;
                exit(1);
        }
        getFiles(".", test);
        for (int i = 0; i < test.size(); i++) {
//              cout << test[i] << endl;
                m.addObject(test[i]);
        }*/
        Vector3<double> pos = Vector3<double>(1, 1, 1);
        Vector3<double> normal = Vector3<double>(0, 0, 1);
        Vector3<double> up = Vector3<double>(0, 1, 0);

        Camera * cam = new Camera(string("primary"), pos, normal, up, 1.0);

        Wireframe * frame = new Wireframe("default", -256, -256, 256, 256, 1);
        Renderer r = Renderer(cam);
        r.set_frame(frame);

        vector<Light *> lights;
        lights.push_back(new Light(0, 0, 0, 0, 0,   0,   0));
        lights.push_back(new Light(8, 8, 8, 1, 250, 250, 250));
        lights.push_back(new Light(2, 7, 6, 1, 250, 250, 250));
        //m.getFaces()

        /*cout << "what?" << endl;
        for (int i = 0; i < m.getFaces().size(); i++) {
                cout << i << endl;
        }*/
        r.prepareRaycast(m.getFaces(), lights);

        ofstream output;

        output.open(argv[2]);
        output << (r);
        output.close();
}
#endif
