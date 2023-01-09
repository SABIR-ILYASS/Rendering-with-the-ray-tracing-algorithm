/*
code file created by ilyass SABIR
*/

#ifndef TRIANGLE_h
#define TRIANGLE_h
#include "Vec3.h"
#include "Ray.h"
#include "Texture.h"
#include <tuple>

using namespace std;

class Triangle
{
public:
	Triangle(Point3 p1, Point3 p2, Point3 p3);

	Point3 getFistPoint() { return p1_; }
	Point3 getSecondPoint() { return p2_; }
	Point3 getThirdPoint() { return p3_; }

	bool insideTriangle(Point3 P);
	Point3 equationOfPlan();

	double atIntersection(const Ray& r);
	double intersection(const Ray& r);

	// tuple<double, double, double> applyTexture(Texture texture, Point3 pos);
	tuple<double, double, double> applyTexture(Point3 pos);

private:
	Point3 p1_;
	Point3 p2_;
	Point3 p3_;
	Point3 equationOfPlan_;
};

#endif