#ifndef GL_WINDOW_OBJ_H
#define GL_WINDOW_OBJ_H

class GameWindow {
    private:
		unsigned int width;
		unsigned int height;
    public:
	   GameWindow(int size_x, int size_y);
	   unsigned int getWidth();
	   unsigned int getHeight();
	   void setHeight(unsigned int h);
	   void setWidth(unsigned int w);
};

#endif