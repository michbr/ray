
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "sphere.h"
#include <cmath>
#include <cfloat>

using namespace std;


Collision::Collision(): normal(0, 0, 0), distance(DBL_MAX), material(0) {}

Collision::Collision(const Collision &source): normal(source.normal), position(source.position), distance(source.distance), material(source.material){}
