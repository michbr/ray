#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include "window.h"
#include "worldModel/camera.h"

#include <GL/glew.h>
#include <list>
#include <worldModel/worldModel.h>


class GLRenderer {
public:
	GLRenderer(GameWindow &win, Camera *cam);

	void add(std::string fileName);


	//static Renderer & getInstance();
	void render();

//	Camera &getCam();

private:
	// GameWindow & window;
	//static bool initialized;
	//static Renderer & instance;
	Camera *cam;
	WorldModel * world;
	std::list<GLuint> buffers;

	void initGL(GameWindow &win);
	void initialize(GameWindow &win);
};

#endif // GL_RENDERER_OBJ_H