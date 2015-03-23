#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN 
#include "glew.h"
#include "wglew.h"
#include "dragon.h"

#pragma comment(lib, "glew32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HDC g_HDC;
bool fullScreen = false;

void SetupPixelFormat(HDC hDC)
{
        /*      Pixel format index
        */
        int nPixelFormat;

        static PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
                1,                                      //default version
                PFD_DRAW_TO_WINDOW |                    //window drawing support
                PFD_SUPPORT_OPENGL |                    //opengl support
                PFD_DOUBLEBUFFER,                       //double buffering support
                PFD_TYPE_RGBA,                          //RGBA color mode
                32,                                     //32 bit color mode
                0, 0, 0, 0, 0, 0,                       //ignore color bits
                0,                                      //no alpha buffer
                0,                                      //ignore shift bit
                0,                                      //no accumulation buffer
                0, 0, 0, 0,                             //ignore accumulation bits
                16,                                     //16 bit z-buffer size
                0,                                      //no stencil buffer
                0,                                      //no aux buffer
                PFD_MAIN_PLANE,                         //main drawing plane
                0,                                      //reserved
                0, 0, 0 };                              //layer masks ignored

                /*      Choose best matching format*/
                nPixelFormat = ChoosePixelFormat(hDC, &pfd);

                /*      Set the pixel format to the device context*/
                SetPixelFormat(hDC, nPixelFormat, &pfd);
}

int WinMain( HINSTANCE hInstance,  HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nShowCmd ) {
	 WNDCLASSEX windowClass; //window class
        HWND    hwnd;                   //window handle
        MSG             msg;                    //message
        bool    done;                   //flag for completion of app
        DWORD   dwExStyle;              //window extended style
        DWORD   dwStyle;                //window style
        RECT    windowRect;

        /*      Screen/display attributes*/
		//GameWindow win = GameWindow(600, 600);
       // int width = 600;
        //int height = 600;
        int bits = 32;

        windowRect.left =(long)0;               //set left value to 0
        windowRect.right =(long)600;  //set right value to requested width
        windowRect.top =(long)0;                //set top value to 0
        windowRect.bottom =(long)600;//set bottom value to requested height

        /*      Fill out the window class structure*/
        windowClass.cbSize                      = sizeof(WNDCLASSEX);
        windowClass.style                       = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc         = WndProc;
        windowClass.cbClsExtra          = 0;
        windowClass.cbWndExtra          = 0;
        windowClass.hInstance           = hInstance;
        windowClass.hIcon                       = LoadIcon(NULL, IDI_APPLICATION);
        windowClass.hCursor                     = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground       = NULL;
        windowClass.lpszMenuName        = NULL;
        windowClass.lpszClassName       = "MyClass";
        windowClass.hIconSm                     = LoadIcon(NULL, IDI_WINLOGO);

        /*      Register window class*/
        if (!RegisterClassEx(&windowClass))
        {
                return 0;
        }

        /*      Check if fullscreen is on*/
        if (fullScreen)
        {
                DEVMODE dmScreenSettings;
                memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
                dmScreenSettings.dmSize = sizeof(dmScreenSettings);
                dmScreenSettings.dmPelsWidth = 600;   //screen width
                dmScreenSettings.dmPelsHeight = 600; //screen height
                dmScreenSettings.dmBitsPerPel = bits;   //bits per pixel
                dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

                if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN !=
                                                                  DISP_CHANGE_SUCCESSFUL))
                {
                        /*      Setting display mode failed, switch to windowed*/
                        MessageBox(NULL, "Display mode failed", NULL, MB_OK);
                        fullScreen = false;
                }
        }

        /*      Check if fullscreen is still on*/
        if (fullScreen)
        {
                dwExStyle = WS_EX_APPWINDOW;    //window extended style
                dwStyle = WS_POPUP;                             //windows style
                ShowCursor(FALSE);                              //hide mouse pointer
        }

        else
        {
                dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //window extended style
                dwStyle = WS_OVERLAPPEDWINDOW;                                  //windows style
        }

        AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

        /*      Class registerd, so now create our window*/
        hwnd = CreateWindowEx(NULL, "MyClass",  //class name
                                                  "Dragon",       //app name
                                                  dwStyle |
                                                  WS_CLIPCHILDREN |
                                                  WS_CLIPSIBLINGS,
                                                  0, 0,                         //x and y coords
                                                  windowRect.right - windowRect.left,
                                                  windowRect.bottom - windowRect.top,//width, height
                                                  NULL,                 //handle to parent
                                                  NULL,                 //handle to menu
                                                  hInstance,    //application instance
                                                  NULL);                //no xtra params

        /*      Check if window creation failed (hwnd = null ?)*/
        if (!hwnd)
        {
                return 0;
        }

        ShowWindow(hwnd, SW_SHOW);      //display window
        UpdateWindow(hwnd);                     //update window

        done = false;   //initialize loop condition variable

        /*      Main message loop*/
		DragonEngine engine = DragonEngine();
		engine.initWindow(600, 600);
		engine.placeCamera (
					0, 0, 8.,
					0, 0, 0,
					0., 1., 0.
					);
		//engine.initRenderer();
		//Renderer rend = Renderer(win);
		//*cam = rend.getCam();
        while (!done)
        {
                PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);

                        if (msg.message == WM_QUIT) { //did we receive a quit message?
							done = true;
                        }
						if (msg.message == WM_MOUSEMOVE) {
							POINT p;
//							if(GetCursorPos(&p))
//								engine.motionEvent(p.x, p.y);
						}
                        else {
							TranslateMessage(&msg);
							DispatchMessage(&msg);
                        }
						engine.render();
						SwapBuffers(g_HDC);
        }

        if (fullScreen) {
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
        }

        return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
/*      Rendering and Device Context
                variables are declared here.
        */
        static HGLRC hRC;
        static HDC hDC;

        /*      Width and Height for the
                window our robot is to be
                displayed in.        */

        int width, height;

        switch(message) {
                case WM_CREATE: //window being created
                        hDC = GetDC(hwnd);  //get current windows device context
                        g_HDC = hDC;
                        SetupPixelFormat(hDC); //call our pixel format setup function
                        /*      Create rendering context and make it current

                        */

                        hRC = wglCreateContext(hDC);
                        wglMakeCurrent(hDC, hRC);

                        return 0;
                        break;
                case WM_CLOSE:  //window is closing
                        /*      Deselect rendering context and delete it*/
                        wglMakeCurrent(hDC, NULL);
                        wglDeleteContext(hRC);

                        /*      Send quit message to queue*/
                        PostQuitMessage(0);

                        return 0;
                        break;
                case WM_SIZE:
                        /*      Retrieve width and height*/
                        height = HIWORD(lParam);
                        width = LOWORD(lParam);

                        /*      Don't want a divide by 0*/
                        if (height == 0) {
                                height = 1;
                        }
						glViewport(0, 0, width, height);
						//win.setHeight(height);
						//win.setWidth(width);
						//rend = Render(win);
						//engine.render();
						//rend.render();
						SwapBuffers(g_HDC);
                        return 0;
                        break;
                default:
                        break;
        }

        return (DefWindowProc(hwnd, message, wParam, lParam));
}

#endif