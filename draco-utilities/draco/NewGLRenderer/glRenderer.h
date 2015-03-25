#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include "window.h"
#include "worldModel/renderer.h"
#include "worldModel/camera.h"

#include <GL/glew.h>
#include <list>
#include <worldModel/worldModel.h>


class GLRenderer: public Renderer {
public:
	GLRenderer(GameWindow &win, Camera *cam);
	void setWorld(WorldModel &world);

	void addObject(SceneObject *object);
	void removeObject(SceneObject *object);


	//static Renderer & getInstance();
	void render();

//	Camera &getCam();

private:
	// GameWindow & window;
	//static bool initialized;
	//static Renderer & instance;
	Camera *cam;
	WorldModel * world;
	std::unordered_map<SceneObject*, GLuint> buffers;

	void initGL(GameWindow &win);
	void initialize(GameWindow &win);
};

#endif // GL_RENDERER_OBJ_H