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
    double x, y, z, w;
    double length() const;
    void normalize();
    Quaternion normalized() const;
    Quaternion conjugate() const;
    Quaternion operator*(Quaternion a, Quaternion b);
private:
    
};

#endif	/* QUATERNION_H */

