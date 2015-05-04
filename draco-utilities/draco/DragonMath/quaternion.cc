#include "dragonmath.h"

#include <cmath>

Quaternion::Quaternion(double x_val, double y_val, double z_val, double w_val) {
    x = x_val;
    y = y_val;
    z = z_val;
    w = w_val;
}

void Quaternion::normalize() {
    double L = length();
    x /= L;
    y /= L;
    z /= L;
    w /= L;
}

Quaternion Quaternion::normalized() const {
    double L = length();
    double x_val = x/L;
    double y_val = y/L;
    double z_val = z/L;
    double w_val = w/L;
    return Quaternion(x_val, y_val, z_val, w_val);
}

Quaternion Quaternion::conjugate() const {
  double x_val = -x;
  double y_val = -y;
  double z_val = -z;
  return Quaternion(x_val, y_val, z_val, w);
}

double Quaternion::length() const {
    return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::operator*(Quaternion B) {

  double x_val = w*B.x + x*B.w + y*B.z - z*B.y;
  double y_val = w*B.y - x*B.z + y*B.w + z*B.x;
  double z_val = w*B.z + x*B.y - y*B.x + z*B.w;
  double w_val = w*B.w - x*B.x - y*B.y - z*B.z;
    return Quaternion(x_val, y_val, z_val, w_val);
}