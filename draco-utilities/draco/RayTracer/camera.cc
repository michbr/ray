//
// Created by brian on 4/9/2015.
//

#include "camera.h"

Camera::Camera(Vector3<double> cameraPosition, Vector3<double> viewPlaneNormal, Vector3<double> upDirection, double focalLength) 
    : position(cameraPosition), vpn(viewPlaneNormal), up(upDirection) {
    this->focalLength = focalLength;
}


Vector3<double> Camera::getFocalPoint() const {
	return position + vpn;
}

Vector3<double> Camera::getHorizontalAxis() const {
        Vector3<double> n = vpn.normal();
        Vector3<double> u = up.normal().cross(n).normal();
        return u;
}

Vector3<double> Camera::getVerticalAxis() const {
        Vector3<double> n = vpn.normal();
        Vector3<double> u = up.normal().cross(n).normal();
        Vector3<double> v = n.cross(u).normal();

        return v;
}
