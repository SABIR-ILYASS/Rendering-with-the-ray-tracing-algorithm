#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle(Point3 point1, Point3 point2, Point3 point3)
{
	this->p1_ = point1;
	this->p2_ = point2;
	this->p3_ = point3;

	this->equationOfPlan_ = this->equationOfPlan();
}

bool Triangle::insideTriangle(Point3 P)
{
	double x1 = dot(cross(p1_ - p2_, p1_ - p3_), cross(p1_ - p2_, p1_ - P));
	double x2 = dot(cross(p2_ - p3_, p2_ - p1_), cross(p2_ - p3_, p2_ - P));
	double x3 = dot(cross(p3_ - p1_, p3_ - p2_), cross(p3_ - p1_, p3_ - P));



	if (x1 > 0 && x2 > 0 && x3 > 0)
		return true;
	else
		return false;

}

double det2(double a, double b, double c, double d)
{
	return a * d - b * c;
}

// le determinant par la méthode de sarrus
double det3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32
		- a13 * a22 * a31 - a11 * a23 * a32 - a12 * a21 * a33;
}

Point3 Triangle::equationOfPlan()
{
	// on cherche une droite de la forme ax+by+cz = 1
	// M�hotde de Sarrus
	double determinant = det3(p1_.x(), p1_.y(), p1_.z(), p2_.x(), p2_.y(), p2_.z(), p3_.x(), p3_.y(), p3_.z());

	double invDeterminant = 1 / determinant;

	double c1, c2, c3, c4, c5, c6, c7, c8, c9;

	c1 = invDeterminant * det2(p2_.y(), p2_.z(), p3_.y(), p3_.z());
	c2 = -invDeterminant * det2(p2_.x(), p2_.z(), p3_.x(), p3_.z());
	c3 = invDeterminant * det2(p2_.x(), p2_.y(), p3_.x(), p3_.y());

	c4 = -invDeterminant * det2(p1_.y(), p1_.z(), p3_.y(), p3_.z());
	c5 = invDeterminant * det2(p1_.x(), p1_.z(), p3_.x(), p3_.z());
	c6 = -invDeterminant * det2(p1_.x(), p1_.y(), p3_.x(), p3_.y());

	c7 = invDeterminant * det2(p1_.y(), p1_.z(), p2_.y(), p2_.z());
	c8 = -invDeterminant * det2(p1_.x(), p1_.z(), p2_.x(), p2_.z());
	c9 = invDeterminant * det2(p1_.x(), p1_.y(), p2_.x(), p2_.y());

	double interX = c1 + c4 + c7;
	double interY = c2 + c5 + c8;
	double interZ = c3 + c6 + c9;

	return Point3(interX, interY, interZ);
}

double intersectionDroiteRay(Vec3 P1, Vec3 P2, const Ray& r)
{
	double length1 = (r.direction() - P2 + P1).length();
	double length2 = (P1 - r.origin()).length();

	if (length1 == 0)
		return INFINITY;
	else
		return -length2 / length1;
}


double Triangle::atIntersection(const Ray& r) {


	Vec3 produitVec = cross(r.direction(), equationOfPlan_);

	if (produitVec.x() == 0 && produitVec.y() == 0 && produitVec.z() == 0)
	{
		double intersection1 = intersectionDroiteRay(this->p1_, this->p2_, r);
		double intersection2 = intersectionDroiteRay(this->p2_, this->p3_, r);
		double intersection3 = intersectionDroiteRay(this->p3_, this->p1_, r);

		return std::min(intersection1, std::min(intersection2, intersection3));
	}
	else
	{
		double length1 = 1 - dot(equationOfPlan_, r.origin());
		double length2 = dot(equationOfPlan_, r.direction());
		return length2 / length1;
	}
}

double Triangle::intersection(const Ray& r)
{
	double pAt = this->atIntersection(r);
	Point3 inter = r.at(pAt);
	if (!(this->insideTriangle(inter)))
		return -1;
	else {
		return pAt;
	}
}