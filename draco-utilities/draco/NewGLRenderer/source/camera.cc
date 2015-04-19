#include "camera.h"

Camera::Camera(CameraStructure * camStructure) : position(camStructure->position), direction(camStructure->direction), up(camStructure->up) {
    
}

