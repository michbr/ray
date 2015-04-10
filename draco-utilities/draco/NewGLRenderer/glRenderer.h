#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include "GL/glew.h"
#include "window.h"
#include "worldModel/renderer.h"
#include "cameraStructure.h"

#include <list>
#include <worldModel/worldModel.h>


class GLRenderer: public BaseRenderer {
public:
	GLRenderer(int width, int height);
	void setWorld(WorldModel &world);
	WorldModel& getWorld();

	void addObject(SceneObject *object);
	void removeObject(SceneObject *object);

	virtual void setCamera(Camera * cam);


	//static Renderer & getInstance();
	void render();

//	Camera &getCam();

private:
	class BufferInfo {
	public:
		GLuint buffer;
		GLsizei vertexCount;

		BufferInfo():
			buffer(0),
			vertexCount(0) {}
		BufferInfo(GLuint buffer, GLsizei vertexCount):
			buffer(buffer),
			vertexCount(vertexCount) {}
		BufferInfo(const BufferInfo &o):
			buffer(o.buffer),
			vertexCount(o.vertexCount) {}
	};
	// GameWindow & window;
	//static bool initialized;
	//static Renderer & instance;
	WorldModel * world;
	std::unordered_map<SceneObject*, BufferInfo> buffers;

	void initGL(int width, int height);
};

#endif // GL_RENDERER_OBJ_H