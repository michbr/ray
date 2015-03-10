#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include <worldModel/worldModel.h>
#include "window.h"
#include "worldModel/camera.h"

class GLRenderer {
private:
	// GameWindow & window;
	//static bool initialized;
	//static Renderer & instance;
	Camera *cam;
	WorldModel * world;


	void initGL(GameWindow &win);

	void initialize(GameWindow &win);

public:
	GLRenderer(GameWindow &win, Camera *cam);


	//static Renderer & getInstance();
	void render();

	Camera &getCam();
};

#endif
