/*
code file created by ilyass SABIR
*/

#include "Sphere.h"
#include "ListSphere.h"

#include <iostream>

using namespace std;

/* embracing sphere */

// this function computes the determinant of 4 values given to the input
double determinant2(double a11, double a12, double a21, double a22)
{
	return a11 * a22 - a12 * a21;
}

// this function computes the determinant of a matrix of size 2*2 given at the input
double determinant2(vector<double> matrix)
{
	return matrix[0] * matrix[3] - matrix[1] * matrix[2];
}

// this function computes the inverse of a matrix of size 2*2 given at the input
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

// this function computes the transpose of a given matrix at the input
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

// this function calculates the product of two matrices given at the input
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

// this function computes the pseudo inverse of a matrix of size 2*2 
// by applying the Moore-Penrose pseudo-inverse formula
vector<double> pseudoInverse2(vector<double> A)
{
	vector<double> At = transposee(A, 2);
	vector<double> AtA = produitMatrix(At, A, 2);
	vector<double> invAtA = inverseMatrix2(AtA);

	return produitMatrix(invAtA, At, 2);
}

// this function computes the determinant of a matrix of 9 values given to the input by the sarrus method
double determinant3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32
		- a13 * a22 * a31 - a11 * a23 * a32 - a12 * a21 * a33;
}

// this function computes the determinant of a matrix of size 3*3 given at the input by the sarrus method
double determinant3(vector<double> matrix)
{
	return matrix[0] * matrix[4] * matrix[8] + matrix[1] * matrix[5] * matrix[6] + matrix[2] * matrix[3] * matrix[7]
		- matrix[2] * matrix[4] * matrix[6] - matrix[5] * matrix[7] * matrix[8] - matrix[0] * matrix[3] * matrix[8];
}

// this function computes the inverse of a matrix of size 3*3 given at the input
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

// this function computes the pseudo inverse of a matrix of size 3 * 3
// by applying the Moore-Penrose pseudo-inverse formula
vector<double> pseudoInverse3(vector<double> A)
{
	vector<double> At = transposee(A, 3);
	vector<double> AtA = produitMatrix(At, A, 3);
	vector<double> invAtA = inverseMatrix3(AtA);

	return produitMatrix(invAtA, At, 3);
}

// this function determines the sphere that passes through 4 points given in the input
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

	// the coordinates of the center of the sphere:
	double centreX = invMatrixCoeff[0] * matrixResult[0] + invMatrixCoeff[1] * matrixResult[1] + invMatrixCoeff[2] * matrixResult[2];
	double centreY = invMatrixCoeff[3] * matrixResult[0] + invMatrixCoeff[4] * matrixResult[1] + invMatrixCoeff[5] * matrixResult[2];
	double centreZ = invMatrixCoeff[6] * matrixResult[0] + invMatrixCoeff[7] * matrixResult[1] + invMatrixCoeff[8] * matrixResult[2];

	Point3 centre = Point3(centreX, centreY, centreZ);
	double radius = (centre - p1).length();

	return Sphere(centre, radius);
}

// this function determines the sphere that passes through 3 points given in the input
Sphere sphere3points(Point3 p1, Point3 p2, Point3 p3)
{
	// determination of the equation of the plane: ax + by + z = d
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

	// the coordinates of the center of the sphere:
	double centerX = invMatrixCoeff[0] * matrixResult[0] + invMatrixCoeff[1] * matrixResult[1] + invMatrixCoeff[2] * matrixResult[2];
	double centerY = invMatrixCoeff[3] * matrixResult[0] + invMatrixCoeff[4] * matrixResult[1] + invMatrixCoeff[5] * matrixResult[2];
	double centerZ = invMatrixCoeff[6] * matrixResult[0] + invMatrixCoeff[7] * matrixResult[1] + invMatrixCoeff[8] * matrixResult[2];


	Point3 center = Point3(centerX, centerY, centerZ);
	double radius = (center - p1).length();

	return Sphere(center, radius);
}

// this function determines if a point is included in a sphere given in input
bool pointInSphere(Sphere s, Point3 p)
{
	if ((p - s.getCenter()).length() < s.getRadius())
		return true;
	return false;
}

//  This function determines the smallest sphere that passes between a point cloud and 3 points p,q,r 
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

// This function determines the smallest sphere that passes between a point cloud and 2 points p,q
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

// This function determines the smallest sphere that passes between a point cloud and a point p
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

// This function determines the smallest sphere that passes between a point cloud
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

// function to add a sphere to the listSphere
void ListSphere::addSphere(Sphere s)
{
	this->listSphere_.push_back(s);
	this->maxRadius_ = std::max(this->maxRadius_, s.getRadius());
	this->listCenter_.push_back(s.getCenter());

	globaleSphere_ = plusPetitSphere(listCenter_);
	globaleSphere_.setRadius(globaleSphere_.getRadius() + this->maxRadius_);

	numberOfSphere_++;
}

// function to check if there is an intersection between the ray and the enclosing sphere
bool ListSphere::isIntersectGlobalSphere(const Ray& r)
{
	if (globaleSphere_.isIntersect(r))
		return true;
	else
		return false;
}

// function returns the intersection sphere index radius/listSphere and the two intersection positions.
tuple<int, double, double> ListSphere::intersect(const Ray& r)
{
	if (globaleSphere_.isIntersect(r))
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