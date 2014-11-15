
#include "face.h"
#include "material.h"
#include "gtest/gtest.h"
#include <iostream>
#include <cmath>

using namespace std;
class FaceTest : public ::testing::Test {
  protected:
	Face * a, * b;
	Material * mat;
	virtual void SetUp() {
		mat = new Material("default");
		mat->setAmbient(Vector3<double>(.01,.01,.01));
		mat->setDiffuse(Vector3<double>(.8, .8, .8));
		mat->setSpecular(Vector3<double>(.2, .2, .2));
		mat->setShininess(.5);
		mat->setTransparency(1);
		
		a = new Face(mat);
		b = new Face(mat);

		a->addVertex(Vector3<double>(0, 2, 0));
		a->addVertex(Vector3<double>(0, 0, 0));
		a->addVertex(Vector3<double>(2, 0, 0));

		b->addVertex(Vector3<double>(2, 0, 0));
		b->addVertex(Vector3<double>(2, 2, 0));
		b->addVertex(Vector3<double>(0, 2, 0));
	}
};

TEST_F(FaceTest, isInside) {
	Vector3<double> test = Vector3<double>(.5, .5, .5);
	
	ASSERT_TRUE(a->isInside(test));	

	test = Vector3<double>(1.5, 1.5, 1.5);

	ASSERT_FALSE(a->isInside(test));
	ASSERT_TRUE(b->isInside(test));
}

TEST_F(FaceTest, intersect) {
	Vector3<double> focalPoint = Vector3<double>(.5, .5, 1);
	Vector3<double> viewPoint = Vector3<double>(.5, .5, .5);
	double t;
	Vector3<double> temp = a->intersect(focalPoint, viewPoint, &t);
	cout << temp << endl;
	ASSERT_EQ(.5, temp[0]);
	ASSERT_EQ(.5, temp[1]);
	ASSERT_EQ(0, temp[2]);
//	cout << *(a->getNormal()) << endl;
//	cout << temp << endl;
//	cout << a->isInside(temp) << endl;
}
