/*
code file created by ilyass SABIR
*/

#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle(Point3 point1, Point3 point2, Point3 point3)
{
	this->p1_ = point1;
	this->p2_ = point2;
	this->p3_ = point3;

	this->equationOfPlan_ = this->equationOfPlan();
}

// function to test if a point is included in the triangle
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

// this function computes the determinant of 4 values given to the input
double det2(double a, double b, double c, double d)
{
	return a * d - b * c;
}

// this function computes the determinant of 9 values given to the input
double det3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32
		- a13 * a22 * a31 - a11 * a23 * a32 - a12 * a21 * a33;
}

// this function determines the equation of the triangle plane
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

// this function returns the point of intersection of the line defined by the two points P1 and P2, and the ray r.
double intersectionDroiteRay(Vec3 P1, Vec3 P2, const Ray& r)
{
	double length1 = (r.direction() - P2 + P1).length();
	double length2 = (P1 - r.origin()).length();

	if (length1 == 0)
		return INFINITY;
	else
		return -length2 / length1;
}

// this function returns the point of intersection between the triangle plan and the ray r.
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

// this function returns the point of intersection between the triangle and the ray r.
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

//  function to apply the texture to the triangle

// tuple<double, double, double> Triangle::applyTexture(Texture texture, Point3 pos)
tuple<double, double, double> Triangle::applyTexture(Point3 pos)
{
	// vector<vector<tuple<double, double, double>>> textureData = texture.getTexture();

	// int w = texture.getTextureWidth();
	// int h = texture.getTextureHeight();


	Point3 position = unit_vector(pos);

	Vec3 orthoAC = Vec3(-(p1_.y() - p3_.y()), p1_.x() - p3_.x(), 0);
	Vec3 orthoBC = Vec3(-(p2_.y() - p3_.y()), p2_.x() - p3_.x(), 0);

	double alpha = dot(pos - p3_, orthoBC) / dot(p1_ - p3_, orthoBC);
	double beta = dot(pos - p3_, orthoAC) / dot(p2_ - p3_, orthoAC);


	Point3 c = alpha * Point3(1, 0, 0) + beta * Point3(0, 1, 0) + (1 - alpha - beta) * Point3(0, 0, 1);
	
	// int Uint = (int) w * c.x();
	// int Vint = (int) h * c.y();
	
	//return textureData[Vint][Uint];

	return make_tuple(c.x(), c.y(), c.z());

}