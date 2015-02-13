#include "dragonmath.h"
#include "gtest/gtest.h"

#include <iostream>

using namespace std;

TEST(DragonMath, Constructor) {
	Vector3<double> test(1, 2, 3);
	double x = test[0];
	double y = test[1];
	double z = test[2];
	ASSERT_EQ(x, 1);
	ASSERT_EQ(y, 2);
	ASSERT_EQ(z, 3);
}

TEST(DragonMath, Magnitude) {
	Vector3<double> test(2, 4, 4);
	ASSERT_EQ(test.magnitude(), 6);
}

TEST(DragonMath, Scale) {
	Vector3<double> test(1, 2, 3);
	Vector3<double> result = test.scale(2);
        double x = result[0];
        double y = result[1];
        double z = result[2];
        ASSERT_EQ(2, x);
        ASSERT_EQ(4, y);
        ASSERT_EQ(6, z);
}

TEST(DragonMath, Dot) {
        Vector3<double> a(1, 2, 3);
        Vector3<double> b (3, 2, 1);
	double result = a.dot(b);
        ASSERT_EQ(10, result);
}

TEST(DragonMath, Assignment) {
	Vector3<double> a(0, 0, 0);
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
        double x = a[0];
        double y = a[1];
        double z = a[2];
        ASSERT_EQ(1, x);
        ASSERT_EQ(2, y);
        ASSERT_EQ(3, z);
}

