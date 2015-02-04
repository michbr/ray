#ifndef IMAGE_WIDGET_OBJ
#define IMAGE_WIDGET_OBJ

#include <FL/Fl_Box.H>

class ImageBox : public Fl_Box {
protected:
 void draw(void);
                int iw;
                int ih;
                int id;
                const unsigned char * data;
public:
  ImageBox(const unsigned char * imageData, int x,int y,int w,int h,const char *l=0)
    :Fl_Box(FL_DOWN_BOX,x,y,w,h,l){
	data = imageData;
	label("");
  }
};
#endif
