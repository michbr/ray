#include "camera.h"

#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
//#include <GL/glu.h>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

using namespace std;

template <class T> Camera<T>::Camera(T x, T y, T z, T vrp_x, T vrp_y, T vrp_z, T upx, T upy, T upz) 
	: pos(x, y, z), look(vrp_x, vrp_y, vrp_z), up(upx, upy, upz) {
}

template <class T> void Camera<T>::LookAt(T vrp_x, T vrp_y, T vrp_z) {
	
	look[0] = vrp_x;
	look[1] = vrp_y;
	look[2] = vrp_z;
	Look();

}

template <class T> void Camera<T>::Look() {
	//gluLookAt(pos[0], pos[1], pos[2], look[0], look[1], look[2], up[0], up[1], up[2]);
	//cout << "here " << *this << endl;
	//cout << look << endl;
	Matrix<T> M = Matrix<T>(4, 4);
	//cout << "pos: " << pos << endl;
	Vector3<T> F = look - pos;
	//cout << "F: " << F << endl;
	F.normalize();
	up.normalize();
	//cout << "f: " << F << endl;
	
	Vector3<T> s = up.cross(F);
	
	s.normalize();
	//cout << "s: " << s << endl;
	Vector3<T> u = s.cross(F);
	u.normalize();
	//cout << "u: " << u << endl;
	
	M(0,0) = s[0];
	M(1,0) = s[1];
	M(2,0) = s[2];
	M(3,0) = 0;
	
	M(0,1) = u[0];
	M(1,1) = u[1];
	M(2,1) = u[2];
	M(3,1) = 0;
	
	M(0,2) = -F[0];
	M(1,2) = -F[1];
	M(2,2) = -F[2];
	M(3,2) = 0;
	
	M(0,3) = 0;
	M(1,3) = 0;
	M(2,3) = 0;
	M(3,3) = 1;

	//cout << M << endl;
	//glMatrixMode( GL_PROJECTION );
	//cout << M << endl;
	//glTranslated(-pos[0], -pos[1], -pos[2]);
	glMultMatrixf(M.toArray());
	glTranslated(-pos[0], -pos[1], -pos[2]);
}

template <class T> void Camera<T>::setPerspective(T fovy, T aspect, T zNear, T zFar) {
//glLoadIdentity();
	//cout << "persp look " << look << endl;
	/*Matrix<T> M = Matrix<T>(4,4);
	T f = tan(M_PI_2 - (fovy/2)); //cotangent of fovy/2
	
	M(0, 0) = f/aspect_ratio;
	M(1,0) = 0;
	M(2,0) = 0;
	M(3,0) = 0;
	
	M(0, 1) = 0;
	M(1,1) = f;
	M(2,1) = 0;
	M(3,1) = 0;
	
	M(0, 2) = 0;
	M(1,2) = 0;
	M(2,2) = (near_plane + far_plane)/(near_plane - far_plane);
	M(3,2) = (2*near_plane*far_plane)/(near_plane - far_plane);
	
	M(0,3) = 0;
	M(1,3) = 0;
	M(2,3) = -1;
	M(3,3) = 0;
	
	cout << M << endl;
	
	//glLoadIdentity();
	glMultMatrixf(M.toArray());
	//Look();*/
	double xmin, xmax, ymin, ymax;
    ymax = zNear * tan(fovy * M_PI / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

template <class T> void Camera<T>::rotate(T delta, int axis) {
	//cout << *this << endl;
	//look.normalize();
	//cout << "hi" << endl;
	//cout << axis << endl;
	//cout << look << endl;
	
	//Vector3<GLfloat> lookDir = look - pos;
	//lookDir.normalize();
	int axis2 = 2;
	//if (axis == 1) {
	//	axis2 = 1;
	//	axis = 2;
	//}
	GLfloat cam_x = look[axis] - pos[axis];
	GLfloat cam_z = look[axis2] - pos[axis2];
	//cout << "hi" << endl;
	//cout << look << endl;
	//cout << pos << endl;
	//cout << "end" << endl;
	GLfloat magnitude = sqrt(cam_x*cam_x + cam_z*cam_z);

	GLfloat angle = acos(cam_z/magnitude);
	if (cam_x < 0) {
		angle = -abs(angle);
	}
	else {
		angle = abs(angle);		
	}

	look[axis] = sin(angle + delta) + pos[axis];
	look[axis2] = cos(angle + delta) + pos[axis2];
	//look.normalize();
	//look[2 - (axis + 1)] = lookDir[2 - (axis + 1)] + pos[2 - (axis + 1)];
	Vector3<GLfloat> test = look - pos;
	test.normalize();
	cout << test << endl;
}

/*
calc_angle(move_y, RWindow::cam_y, RWindow::cam_z, &RWindow::vrp_y, &RWindow::vrp_z);

GLfloat RWindow::calc_angle(GLfloat move, GLfloat cam_1, GLfloat cam_2, GLfloat *vrp_1, GLfloat *vrp_2 ) {
	GLfloat cam_x = *vrp_1 - cam_1;
	GLfloat cam_z = RWindow::vrp_z - RWindow::cam_z;

	GLfloat magnitude = sqrt(cam_x*cam_x + cam_z*cam_z);

	GLfloat angle = acos(cam_z/magnitude);
	if (cam_x < 0) {
		angle = -abs(angle);
	}
	else {
		angle = abs(angle);		
	}

	*vrp_1 = sin(angle - LOOK_SENSITIVITY*move) + cam_1;
	RWindow::vrp_z = cos(angle - LOOK_SENSITIVITY*move) + RWindow::cam_z;
}*/

template class Camera<GLfloat>;
