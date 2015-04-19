//
// Created by brian on 4/9/2015.
//

#ifndef DRACO_CAMERA_H
#define DRACO_CAMERA_H

#include "DragonMath/dragonmath.h"

class Camera {
private:
    double focalLength;
public:
    Vector3<double> position, vpn, up;
    Camera(Vector3<double> cameraPosition, Vector3<double> viewPlaneNormal, Vector3<double> upDirection, double focalLength);
    Vector3<double> getFocalPoint() const;
    Vector3<double> getHorizontalAxis() const;
    Vector3<double> getVerticalAxis() const;
};


#endif //DRACO_CAMERA_H
