//#include "SphereEnglobant.h"
#include "Vec3.h"
#include "Ray.h"


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
private:
	Point3 p1_;
	Point3 p2_;
	Point3 p3_;
	Point3 equationOfPlan_;
};