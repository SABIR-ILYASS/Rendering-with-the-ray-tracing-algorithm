/*
code file created by ilyass SABIR
*/

#ifndef LISTSPHERE_h
#define LISTSPHERE_h

#include "Sphere.h"

#include <tuple>

using namespace std;

class ListSphere : public Sphere
{
public:
    ListSphere();
    void addSphere(Sphere s);

    bool isIntersectGlobalSphere(const Ray& r);
    tuple<int, double, double> intersect(const Ray& r);

private:
    vector<Sphere> listSphere_;
    Sphere globaleSphere_;
    vector<Point3> listCenter_;
    double maxRadius_;
    int numberOfSphere_;
};

#endif

