#include "Sphere.h"
// #include "SphereEnglobant.h"

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

bool Sphere::isIntersect(const Ray& r) {
    Vec3 oc = r.origin() - this->center_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - this->radius_ * this->radius_;
    auto discriminant = half_b * half_b - a * c;

    return (discriminant > 0);
}


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


double Sphere::applyTexture(Texture texture, Point3 pos)
{
	const double PI = 3.14159265358979323846;

	vector<vector<int>> textureData = texture.getTexture();


	//cout << texture_.size() <<" h " << texture_[0].size() << endl;

	int w = texture.getTextureWidth();
	int h = texture.getTextureHeight();

	//double ratio = h / height;
	
	//Point3 position = unit_vector(cross(pos, this->center_));
	Point3 position = unit_vector(pos - this->center_);

	double u = 0.5 + atan2(position.z(), position.x()) / (2 * PI);
	double v = 0.5 - asin(position.y()) / PI;

	if (v < 0) v += 2 * PI;

	int Uint = (int) w * u;
	int Vint = (int)h * v;

	return textureData[Vint][Uint] / 255.999;
}

Texture::Texture(string path)
{
	ifstream myfile;
	myfile.open(path, ios::in);

	string content;
	int count = 0;
	myfile >> content;

	myfile >> content;
	width_ = std::stoi(content);

	myfile >> content;
	height_ = std::stoi(content);

	myfile >> content;

	for (int i = 0; i < height_; i++)
	{
		vector<int> matrixi;
		for (int j = 0; j < 3 * width_; j++)
		{
			myfile >> content;
			if (count == 0)
			{
				matrixi.push_back(std::stoi(content));
			}
			count = (count + 1) % 3;
		}
		texture_.push_back(matrixi);
	}

}

Texture::~Texture()
{
	this->texture_.clear();
}


// sphere englobante

double determinant2(double a11, double a12, double a21, double a22)
{
	return a11 * a22 - a12 * a21;
}

double determinant2(vector<double> matrix)
{
	return matrix[0] * matrix[3] - matrix[1] * matrix[2];
}

vector<double> inverseMatrix2(vector<double> matrix)
{
	double determinant = determinant2(matrix);

	vector<double> result;
	result.push_back(matrix[3] / determinant);
	result.push_back(-matrix[2] / determinant);
	result.push_back(-matrix[1] / determinant);
	result.push_back(matrix[0] / determinant);

	return result;
}

vector<double> transposee(vector<double> matrix, int size)
{
	vector<double> transposee;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		{
			int index = i + j * size;
			transposee.push_back(matrix[index]);
		}
	}
	return transposee;
}

vector<double> produitMatrix(vector<double> matrix1, vector<double> matrix2, int size)
{
	vector<double> produit;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double cij = 0;
			for (int k = 0; k < size; k++)
			{
				int index1 = i * size + k;
				int index2 = j + size * k;
				cij += matrix1[index1] * matrix2[index2];
			}
			produit.push_back(cij);
		}
	}
	return produit;
}

// formule de pseudo inverse Moore-Penrose inverse
vector<double> pseudoInverse2(vector<double> A)
{
	vector<double> At = transposee(A, 2);
	vector<double> AtA = produitMatrix(At, A, 2);
	vector<double> invAtA = inverseMatrix2(AtA);

	return produitMatrix(invAtA, At, 2);
}

// le determinant par la méthode de sarrus
double determinant3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32
		- a13 * a22 * a31 - a11 * a23 * a32 - a12 * a21 * a33;
}

double determinant3(vector<double> matrix)
{
	return matrix[0] * matrix[4] * matrix[8] + matrix[1] * matrix[5] * matrix[6] + matrix[2] * matrix[3] * matrix[7]
		- matrix[2] * matrix[4] * matrix[6] - matrix[5] * matrix[7] * matrix[8] - matrix[0] * matrix[3] * matrix[8];
}

vector<double> inverseMatrix3(vector<double> matrix)
{
	double determinant = determinant3(matrix);

	vector<double> inverse;

	double inv0 = determinant2(matrix[4], matrix[5], matrix[7], matrix[8]) / determinant;
	double inv1 = -determinant2(matrix[3], matrix[5], matrix[6], matrix[8]) / determinant;
	double inv2 = determinant2(matrix[3], matrix[4], matrix[6], matrix[7]) / determinant;

	double inv3 = -determinant2(matrix[1], matrix[2], matrix[7], matrix[8]) / determinant;
	double inv4 = determinant2(matrix[0], matrix[2], matrix[6], matrix[8]) / determinant;
	double inv5 = -determinant2(matrix[0], matrix[1], matrix[6], matrix[7]) / determinant;

	double inv6 = determinant2(matrix[1], matrix[2], matrix[4], matrix[5]) / determinant;
	double inv7 = -determinant2(matrix[0], matrix[2], matrix[3], matrix[5]) / determinant;
	double inv8 = determinant2(matrix[0], matrix[1], matrix[3], matrix[4]) / determinant;

	inverse.push_back(inv0);
	inverse.push_back(inv3);
	inverse.push_back(inv6);
	inverse.push_back(inv1);
	inverse.push_back(inv4);
	inverse.push_back(inv7);
	inverse.push_back(inv2);
	inverse.push_back(inv5);
	inverse.push_back(inv8);

	return inverse;
}

// formule de pseudo inverse Moore-Penrose inverse
vector<double> pseudoInverse3(vector<double> A)
{
	vector<double> At = transposee(A, 3);
	vector<double> AtA = produitMatrix(At, A, 3);
	vector<double> invAtA = inverseMatrix3(AtA);

	return produitMatrix(invAtA, At, 3);
}


Sphere sphere4Points(Point3 p1, Point3 p2, Point3 p3, Point3 p4)
{
	vector<double> matrixCoeff;

	matrixCoeff.push_back(2 * (p1.x() - p4.x()));
	matrixCoeff.push_back(2 * (p1.y() - p4.y()));
	matrixCoeff.push_back(2 * (p1.z() - p4.z()));

	matrixCoeff.push_back(2 * (p2.x() - p4.x()));
	matrixCoeff.push_back(2 * (p2.y() - p4.y()));
	matrixCoeff.push_back(2 * (p2.z() - p4.z()));

	matrixCoeff.push_back(2 * (p3.x() - p4.x()));
	matrixCoeff.push_back(2 * (p3.y() - p4.y()));
	matrixCoeff.push_back(2 * (p3.z() - p4.z()));

	vector<double> matrixResult;

	matrixResult.push_back(pow(p1.x(), 2) - pow(p4.x(), 2) + pow(p1.y(), 2) - pow(p4.y(), 2) + pow(p1.z(), 2) - pow(p4.z(), 2));
	matrixResult.push_back(pow(p2.x(), 2) - pow(p4.x(), 2) + pow(p2.y(), 2) - pow(p4.y(), 2) + pow(p2.z(), 2) - pow(p4.z(), 2));
	matrixResult.push_back(pow(p3.x(), 2) - pow(p4.x(), 2) + pow(p3.y(), 2) - pow(p4.y(), 2) + pow(p3.z(), 2) - pow(p4.z(), 2));

	vector<double> invMatrixCoeff = pseudoInverse3(matrixCoeff);

	// les coordonnées du centre de la sphére:
	double centreX = invMatrixCoeff[0] * matrixResult[0] + invMatrixCoeff[1] * matrixResult[1] + invMatrixCoeff[2] * matrixResult[2];
	double centreY = invMatrixCoeff[3] * matrixResult[0] + invMatrixCoeff[4] * matrixResult[1] + invMatrixCoeff[5] * matrixResult[2];
	double centreZ = invMatrixCoeff[6] * matrixResult[0] + invMatrixCoeff[7] * matrixResult[1] + invMatrixCoeff[8] * matrixResult[2];

	Point3 centre = Point3(centreX, centreY, centreZ);
	double radius = (centre - p1).length();

	return Sphere(centre, radius);
}


Sphere sphere3points(Point3 p1, Point3 p2, Point3 p3)
{
	// determination de l'équation du plan: ax + by + z = d
	vector<double> matrixPlan;
	matrixPlan.push_back(p1.x() - p3.x());
	matrixPlan.push_back(p1.y() - p3.y());
	matrixPlan.push_back(p2.x() - p3.x());
	matrixPlan.push_back(p2.y() - p3.y());

	vector<double> planResult;
	planResult.push_back(p3.z() - p1.z());
	planResult.push_back(p3.z() - p2.z());

	vector<double> result = pseudoInverse2(matrixPlan);

	double a = result[0] * planResult[0] + result[1] * planResult[1];
	double b = result[2] * planResult[0] + result[3] * planResult[1];
	double d = a * p1.x() + b * p1.y() + p1.z();

	vector<double> matrixCoeff;
	matrixCoeff.push_back(2 * (p1.x() - p3.x()));
	matrixCoeff.push_back(2 * (p1.y() - p3.y()));
	matrixCoeff.push_back(2 * (p1.z() - p3.z()));

	matrixCoeff.push_back(2 * (p2.x() - p3.x()));
	matrixCoeff.push_back(2 * (p2.y() - p3.y()));
	matrixCoeff.push_back(2 * (p2.z() - p3.z()));

	matrixCoeff.push_back(a);
	matrixCoeff.push_back(b);
	matrixCoeff.push_back(1);

	vector<double> matrixResult;
	matrixResult.push_back(pow(p1.x(), 2) - pow(p3.x(), 2) + pow(p1.y(), 2) - pow(p3.y(), 2) + pow(p1.z(), 2) - pow(p3.z(), 2));
	matrixResult.push_back(pow(p2.x(), 2) - pow(p3.x(), 2) + pow(p2.y(), 2) - pow(p3.y(), 2) + pow(p2.z(), 2) - pow(p3.z(), 2));
	matrixResult.push_back(d);

	vector<double> invMatrixCoeff = pseudoInverse3(matrixCoeff);

	// les coordonnées du centre de la sphére:
	double centerX = invMatrixCoeff[0] * matrixResult[0] + invMatrixCoeff[1] * matrixResult[1] + invMatrixCoeff[2] * matrixResult[2];
	double centerY = invMatrixCoeff[3] * matrixResult[0] + invMatrixCoeff[4] * matrixResult[1] + invMatrixCoeff[5] * matrixResult[2];
	double centerZ = invMatrixCoeff[6] * matrixResult[0] + invMatrixCoeff[7] * matrixResult[1] + invMatrixCoeff[8] * matrixResult[2];


	Point3 center = Point3(centerX, centerY, centerZ);
	double radius = (center - p1).length();

	return Sphere(center, radius);
}

bool pointInSphere(Sphere s, Point3 p)
{
	if ((p - s.getCenter()).length() < s.getRadius())
		return true;
	return false;
}

Sphere plusPetitSphereParTroisPoints(vector<Vec3> cloud, Point3 p, Point3 q, Point3 r)
{
	Sphere S = sphere3points(p, q, r);

	for (int k = 0; k < cloud.size(); k++)
	{
		Point3 pk = cloud[k];

		if (!(pointInSphere(S, pk)))
		{
			S = sphere4Points(pk, p, q, r);
		}
	}
	return S;
}

Sphere plusPetitSphereParDeuxPoints(vector<Vec3> cloud, Point3 p, Point3 q)
{
	Sphere S = Sphere((p + q) * 0.5, (p - q).length() * 0.5);

	for (int k = 0; k < cloud.size(); k++)
	{
		Point3 pk = cloud[k];
		if (!(pointInSphere(S, pk)))
		{
			S = plusPetitSphereParTroisPoints({ cloud.begin(), cloud.begin() + k - 1 }, pk, p, q);
		}
	}
	return S;
}

Sphere plusPetitSphereParUnPoint(vector<Vec3> cloud, Point3 p)
{
	Point3 point1 = cloud[0];
	Sphere S = Sphere((point1 + p) * 0.5, (point1 - p).length() * 0.5);

	for (int j = 1; j < cloud.size(); j++)
	{
		Point3 pointJ = cloud[j];
		if (!(pointInSphere(S, pointJ)))
		{
			S = plusPetitSphereParDeuxPoints({ cloud.begin(), cloud.begin() + j - 1 }, pointJ, p);
		}
	}
	return S;
}


Sphere plusPetitSphere(vector<Point3> cloud)
{
	Point3 point1 = cloud[0];
	Point3 point2 = cloud[1];
	Sphere S = Sphere((point1 + point2) * 0.5, (point1 - point2).length() * 0.5);


	for (int i = 2; i < cloud.size(); i++)
	{
		Point3 pointI = cloud[i];
		if (!(pointInSphere(S, pointI)))
		{
			S = plusPetitSphereParUnPoint({ cloud.begin(), cloud.begin() + i - 1 }, pointI);
		}
	}
	return S;

}


// class ListSphere

ListSphere::ListSphere()
{
	globaleSphere_ = Sphere(Point3(0., 0., 0.), 0.);
	maxRadius_ = 0;
	numberOfSphere_ = 0;

}

void ListSphere::addSphere(Sphere s)
{
	this->listSphere_.push_back(s);
	this->maxRadius_ = std::max(this->maxRadius_, s.getRadius());
	this->listCenter_.push_back(s.getCenter());

	globaleSphere_ = plusPetitSphere(listCenter_);
	globaleSphere_.setRadius(globaleSphere_.getRadius() + this->maxRadius_);

	numberOfSphere_++;
}

bool ListSphere::isIntersectGlobalSphere(const Ray& r)
{
	if (globaleSphere_.isIntersect(r))
		return true;
	else
		return false;
}


tuple<int, double, double> ListSphere::intersect(const Ray& r)
{
	if(globaleSphere_.isIntersect(r))
		return  tuple<int, double, double> {-1, 0.0, 0.0};
	else
	{
		// vector<double> listOfIntersection;
		double minIntersection = -INFINITY;
		double minIntersection2 = -INFINITY;
		int index = -1;

		for (int i = 0; i < numberOfSphere_; i++) {
			Sphere sI = listSphere_[i];
			tuple<double, double> intersectionI = sI.intersect(r);
			double interI1 = std::get<0>(intersectionI);
			double interI2 = std::get<1>(intersectionI);

			if (minIntersection > interI1)
			{
				minIntersection = interI1;
				minIntersection2 = interI2;
				index = i;
			}
			//listOfIntersection.push_back(interI1);
		}
		return tuple<int, double, double> {index, minIntersection, minIntersection2};
	}
}
