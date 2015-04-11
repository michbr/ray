#include "cameraStructure.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

using namespace std;

CameraStructure::CameraStructure(Vector3<double> pos, Vector3<double> dir, Vector3<double> up) : position(pos), direction(dir), up(up) {}


//
//Camera::Camera(float x, float y, float z, float vrp_x, float vrp_y, float vrp_z, float upx, float upy, float upz) :
//	position(x, y, z),
//	up(upx, upy, upz),
//	direction((position +Vector3<double>(vrp_x, vrp_y, vrp_z)).normal()) {}

/*Camera::Camera(string camName, Vector3<double> startPos, Vector3<double> vp_normal, Vector3<double> v_up, double d) :
	name(camName),
	position(startPos),
	direction(vp_normal),
	up(v_up),
	nearPlane(d) {}

void Camera::LookAt(Vector3<double> target) {
	direction = (target -position).normal();
}*/

// commented due to lack of GL import.  Should exist in gl camera
//void Camera::Look(Vector3<float> look) {
//	//gluLookAt(pos[0], pos[1], pos[2], look[0], look[1], look[2], up[0], up[1], up[2]);
//	//cout << "here " << *this << endl;
//	//cout << look << endl;
//	Matrix<float> M = Matrix<float>(4, 4);
//	//cout << "pos: " << pos << endl;
//	Vector3<float> posf = Vector3<float>((float)position.x, (float)position.y, (float)position.z);
//	Vector3<float> upf =  Vector3<float>((float)up.x, (float)up.y, (float)up.z);
//
//	Vector3<float> F = look - posf;
//	//cout << "F: " << F << endl;
//	F.normalize();
//	up.normalize();
//	//cout << "f: " << F << endl;
//
//	Vector3<float> s = upf.cross(F);
//
//	s.normalize();
//	//cout << "s: " << s << endl;
//	Vector3<float> u = s.cross(F);
//	u.normalize();
//	//cout << "u: " << u << endl;
//
//	M(0,0) = s[0];
//	M(1,0) = s[1];
//	M(2,0) = s[2];
//	M(3,0) = 0;
//
//	M(0,1) = u[0];
//	M(1,1) = u[1];
//	M(2,1) = u[2];
//	M(3,1) = 0;
//
//	M(0,2) = -F[0];
//	M(1,2) = -F[1];
//	M(2,2) = -F[2];
//	M(3,2) = 0;
//
//	M(0,3) = 0;
//	M(1,3) = 0;
//	M(2,3) = 0;
//	M(3,3) = 1;
//
//	//cout << M << endl;
//	//glMatrixMode( GL_PROJECTION );
//	//cout << M << endl;
//	//glTranslated(-pos[0], -pos[1], -pos[2]);
//	glMultMatrixf(M.toArray());
//	glTranslated(-position[0], -position[1], -position[2]);
//}

// commented due to lack of GL import.  Should exist in gl camera
//void Camera::setPerspective(float fovy, float aspect, float zNear, float zFar) {
////glLoadIdentity();
//	//cout << "persp look " << look << endl;
//	/*Matrix<T> M = Matrix<T>(4,4);
//	T f = tan(M_PI_2 - (fovy/2)); //cotangent of fovy/2
//
//	M(0, 0) = f/aspect_ratio;
//	M(1,0) = 0;
//	M(2,0) = 0;
//	M(3,0) = 0;
//
//	M(0, 1) = 0;
//	M(1,1) = f;
//	M(2,1) = 0;
//	M(3,1) = 0;
//
//	M(0, 2) = 0;
//	M(1,2) = 0;
//	M(2,2) = (near_plane + far_plane)/(near_plane - far_plane);
//	M(3,2) = (2*near_plane*far_plane)/(near_plane - far_plane);
//
//	M(0,3) = 0;
//	M(1,3) = 0;
//	M(2,3) = -1;
//	M(3,3) = 0;
//
//	cout << M << endl;
//
//	//glLoadIdentity();
//	glMultMatrixf(M.toArray());
//	//Look();*/
//	double xmin, xmax, ymin, ymax;
//    ymax = zNear * tan(fovy * M_PI / 360.0);
//    ymin = -ymax;
//    xmin = ymin * aspect;
//    xmax = ymax * aspect;
//    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
//}

// commented due to lack of GL import.  Should exist in gl camera
//void Camera::rotate(float delta, int axis, Vector3<float> look) {
//	//cout << *this << endl;
//	//look.normalize();
//	//cout << "hi" << endl;
//	//cout << axis << endl;
//	//cout << look << endl;
//
//	Vector3<float> posf = Vector3<float>(position[0], position[1], position[2]);
//	//Vector3<GLfloat> lookDir = look - pos;
//	//lookDir.normalize();
//	int axis2 = 2;
//	//if (axis == 1) {
//	//	axis2 = 1;
//	//	axis = 2;
//	//}
//	GLfloat cam_x = look[axis] - posf[axis];
//	GLfloat cam_z = look[axis2] - posf[axis2];
//	//cout << "hi" << endl;
//	//cout << look << endl;
//	//cout << pos << endl;
//	//cout << "end" << endl;
//	GLfloat magnitude = sqrt(cam_x*cam_x + cam_z*cam_z);
//
//	GLfloat angle = acos(cam_z/magnitude);
//	if (cam_x < 0) {
//		angle = -abs(angle);
//	}
//	else {
//		angle = abs(angle);
//	}
//
//	look[axis] = sin(angle + delta) + posf[axis];
//	look[axis2] = cos(angle + delta) + posf[axis2];
//	//look.normalize();
//	//look[2 - (axis + 1)] = lookDir[2 - (axis + 1)] + pos[2 - (axis + 1)];
//	Vector3<float> test = look - posf;
//	test.normalize();
//	//TODO removed because the operator<< implementation doesn't work
//	//cout << test << endl;
//}

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

//string Camera::getName() const {
//	return name;
//}
//
//Vector3<double> Camera::getFocalPoint() const {
//	return position +direction *nearPlane;
//}
//
//Vector3<double> Camera::getHorizontalAxis() const {
//        Vector3<double> n = direction.normal();
//        Vector3<double> u = up.normal().cross(n).normal();
//        return u;
//}
//
//Vector3<double> Camera::getVerticalAxis() const {
//        Vector3<double> n = direction.normal();
//        Vector3<double> u = up.normal().cross(n).normal();
//        Vector3<double> v = n.cross(u).normal();
//
//        return v;
//}


