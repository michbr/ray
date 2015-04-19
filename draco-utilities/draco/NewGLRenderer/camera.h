/* 
 * File:   camera.h
 * Author: brian
 *
 * Created on April 9, 2015, 10:49 PM
 */

#ifndef GL_CAMERA_H
#define	GL_CAMERA_H

#include "DragonMath/dragonmath.h"
#include "worldModel/cameraStructure.h"

class Camera {
public:
    Vector3<double> position, direction, up;
    Camera(CameraStructure * camStructure);
};



#endif	/* CAMERA_H */

