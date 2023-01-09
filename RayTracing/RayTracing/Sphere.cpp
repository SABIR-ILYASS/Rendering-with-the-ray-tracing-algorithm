/*
code file created by ilyass SABIR
*/

#include "Sphere.h"

#include <tuple>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


Sphere::Sphere(Point3 center, double radius)
{
    this->center_ = center;
    this->radius_ = radius;
}

// function tests if there is an intersection between a sphere and a ray
bool Sphere::isIntersect(const Ray& r) {
    Vec3 oc = r.origin() - this->center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - this->radius_ * this->radius_;
    auto discriminant = half_b * half_b - a * c;

    return (discriminant > 0);
}

// function returns the two points of intersection between a sphere and a ray
tuple<double, double> Sphere::intersect(const Ray& r) {

    Vec3 oc = r.origin() - this->center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - this->radius_ * this->radius_;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return tuple<double, double> {-1., -1.};
    }
    else {
        return tuple<double, double> { (-half_b - sqrt(discriminant)) / a, (-half_b + sqrt(discriminant)) / a };
    }
}

// function to apply the texture to the sphere
tuple<double, double, double> Sphere::applyTexture(Texture texture, Point3 pos)
{
	const double PI = 3.14159265358979323846;

	vector<vector<tuple<double, double, double>>> textureData = texture.getTexture();


	//cout << texture_.size() <<" h " << texture_[0].size() << endl;

	int w = texture.getTextureWidth();
	int h = texture.getTextureHeight();

	//double ratio = h / height;
	
	Point3 normal = unit_vector(pos - this->center_);

	double u = 0.5 + atan2(normal.z(), normal.x()) / (2 * PI);
	double v = 0.5 - asin(normal.y()) / PI;

	if (v < 0) v += 2 * PI;

	int Uint = (int) w * u;
	int Vint = (int)h * v;

	return textureData[Vint][Uint];
}
