#ifndef RENDERER_OBJ_H
#define RENDERER_OBJ_H

#include "DragonMath/dragonmath.h"
#include "wireframe.h"
#include "worldModel/face.h"
#include "worldModel/light.h"
#include "camera.h"

#include <vector>


class Renderer {
  private:
	Camera * cam;
	std::vector<std::vector<int> *> * image;
	Wireframe * frame;
	std::vector<std::vector<double> *> * z_buffer;
	bool has_frame;
	long renderPos;
	//void bresenham(std::vector<Vertex> *);
	void fill(int, int, int, int, int);
	std::vector<int> * findClosestFace(Vector3<double>, Vector3<double>, const std::vector<Face *> &, const std::vector<Light *> &, int, double *, bool *);
//	std::vector<int> * find_closest_elipse(std::vector<double> *, std::vector<double> *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light *> &, int, double *, bool *);
	std::vector<int> * colorFacePixel(Vector3<double>, Vector3<double>, Face *, const std::vector<Face *> &, const std::vector<Light * > &, int);
//	std::vector<int> * color_elipse_pixel(std::vector<double> *, std::vector<double> *, const Elipse *, const std::vector<Face *> &, const std::vector<Elipse *> &, const std::vector<Light * > &, int);
  public:
	Renderer(Camera * c);
	void set_frame(Wireframe *);
	long getCurrentPixel();
	std::vector<int> * getPixelColor(long pixelNum);
	size_t getImageWidth();
	size_t getImageHeight();	
	//void prepare_wireframe(std::vector<Group *>);
	void prepareRaycast(const std::vector<Face *> &, const std::vector<Light * > &);
	bool hasFrame();

	friend std::ostream & operator<<(std::ostream &, const Renderer &);
	std::ostream & operator<<(std::ostream &);

};

#endif
