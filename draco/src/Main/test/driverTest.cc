
#include "camera.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cmath>

using namespace std;

TEST(Camera, GetAxes) {
	Vector3<double> * normal = new Vector3<double>(1, 0, 0);
	Vector3<double> * up = new Vector3<double>(0,1,0);
	Camera one = Camera("testCam", 1, 0, 0, 0, normal, up); 
	Vector3<double> h = one.getHorizontalAxis();
	Vector3<double> v = one.getVerticalAxis();

	EXPECT_EQ(0, abs(h[0]));
	EXPECT_EQ(0, abs(h[1]));
	EXPECT_EQ(-1, h[2]);

	EXPECT_EQ(0, abs(v[0]));
	EXPECT_EQ(1, v[1]);
	EXPECT_EQ(0, abs(v[0]));
}

TEST(Camera, GetFocalPoint) {
	Vector3<double> * normal = new Vector3<double>(1, 0, 0);
	Vector3<double> * up = new Vector3<double>(0,1,0);
	Camera one = Camera("testCam", 1, 0, 0, 0, normal, up);
	Vector3<double> fp = one.getFocalPoint();
	EXPECT_EQ(1, fp[0]);
	EXPECT_EQ(0, abs(fp[1]));
	EXPECT_EQ(0, abs(fp[2]));
}