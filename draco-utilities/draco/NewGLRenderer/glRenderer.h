#ifndef GL_RENDERER_OBJ_H
#define GL_RENDERER_OBJ_H

#include "GL/glew.h"
#include "window.h"
#include "worldModel/renderer.h"
#include "WorldModel/cameraStructure.h"
#include "camera.h"

#include <list>
#include <worldModel/worldModel.h>


class GLRenderer: public BaseRenderer {
public:
	void setWorld(WorldModel &world);
	WorldModel& getWorld();

	void addObject(SceneObject *object);
	void removeObject(SceneObject *object);

	virtual void addCamera(CameraStructure * cam);


	//static Renderer & getInstance();
	void render();
	void initGL(int width, int height);

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
	Camera * currentCam;

};

#endif // GL_RENDERER_OBJ_H