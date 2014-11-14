
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
	
}
