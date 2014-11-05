#ifndef R_WINDOW

#define R_WINDOW

#include <string>

using namespace std;

const int SCREEN_FPS = 60;


//Viewport mode
enum ViewPortMode
{
    VIEWPORT_MODE_FULL,
    VIEWPORT_MODE_HALF_CENTER,
    VIEWPORT_MODE_HALF_TOP,
    VIEWPORT_MODE_QUAD,
    VIEWPORT_MODE_RADAR
};

class RWindow {
   public:
	RWindow();	//constructors
	RWindow(string);
	virtual ~RWindow();

	void initGL(int *argc, char** argv);	
	
	string GetWindowTitle() const;	//getters
	
	unsigned short int GetWindowHorizontal() const;
	unsigned short int GetWindowVertical() const;

	unsigned short int GetWindowX() const;
	unsigned short int GetWindowY() const;

	void SetWindowTitle(string);	//setters

	void SetWindowHorizontal(unsigned short int);
	void SetWindowVertical(unsigned short int);

	void SetWindowY(unsigned short int);
	void SetWindowX(unsigned short int);	

	static void init();	//initializers?
	static void display_contents();
	static void render();
	static void handleKeys( unsigned char key, int x, int y );
	static void specialKeys( int key, int x, int y );
	static void PassiveMotion(int x, int y);
	static void runMainLoop( int val );
	static void ReshapeFunc(int width, int height);

   private:
	static GLfloat calc_angle(GLfloat move, GLfloat cam_1, GLfloat cam_2, GLfloat *vrp_1, GLfloat *vrp_2);
	string str_window_title;
	static GLfloat angle;
  	static GLfloat cam_x;
  	static GLfloat cam_y;
  	static GLfloat cam_z;
	static GLfloat vrp_x;
	static GLfloat vrp_y;
	static GLfloat vrp_z;
	static GLfloat up_x;
	static GLfloat up_y;
	static GLfloat up_z;

	static int mouse_x;
	static int mouse_y;

	static void set_camera(GLfloat, GLfloat, GLfloat);
	static unsigned short int usi_hwindow;
	static unsigned short int usi_vwindow;
	static unsigned short int usi_windowx;
	static unsigned short int usi_windowy;

	
};

#endif
