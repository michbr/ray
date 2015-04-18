/* 
 * File:   quaternion.h
 * Author: brian
 *
 * Created on April 17, 2015, 1:01 PM
 */

#ifndef QUATERNION_H
#define	QUATERNION_H

class Quaternion {
public:
    Quaternion(double x_val, double y_val, double z_val, double w_val);
    double x, y, z, w;
    double length() const;
    void normalize();
    Quaternion normalized() const;
    Quaternion conjugate() const;
    Quaternion operator*(Quaternion multiplicand);
private:
    
};

#endif	/* QUATERNION_H */

