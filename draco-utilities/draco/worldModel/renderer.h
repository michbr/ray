
#ifndef DRACO_WORLD_MODEL_RENDERER_H
#define DRACO_WORLD_MODEL_RENDERER_H

#include "sceneObject.h"
#include "cameraStructure.h"
#include "worldModel.h"


#ifdef _WIN32
#	ifdef DLL_IMPORT_DRACO_WORLD_MODEL_RENDERER
#		define DRACO_RENDERER_API __declspec(dllimport)
#	else
#		define DRACO_RENDERER_API __declspec(dllexport)
#	endif
#else
#	define DRACO_RENDERER_API
#endif


class BaseRenderer {
public:
	virtual void addObject(SceneObject *) = 0;
	virtual void removeObject(SceneObject *) = 0;
	virtual void addCamera(CameraStructure * cam) = 0;
protected:
	WorldModel * currentModel;
};


#endif // DRACO_WORLD_MODEL_RENDERER_H