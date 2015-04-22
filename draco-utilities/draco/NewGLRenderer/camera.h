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
private:
    int screenWidth;
    int screenHeight;
    double CurrentRotationX;
public:
    Vector3<double> position, direction, up;
    Camera(CameraStructure * camStructure, int width, int height);
    void SetViewByMouse();
    void rotateCamera(double Angle, double x, double y, double z);
};



#endif	/* CAMERA_H */

