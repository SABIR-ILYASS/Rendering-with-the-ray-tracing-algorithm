#ifndef SPHERE_h
#define SPHERE_h

#include "Vec3.h"
#include "Ray.h"

#include<tuple>
#include <vector>

using namespace std;

class Texture
{
public:
    Texture(string path);
    ~Texture();
    string getPath() { return path_; }
    vector<vector<int>> getTexture() { return texture_; }
    int getTextureWidth() { return width_; }
    int getTextureHeight() { return height_; }


private:
    string path_;
    vector<vector<int>> texture_;
    int width_;
    int height_;
};

class Sphere
{
public:
    Sphere() {}

    Sphere(Point3 center, double radius);

    bool isIntersect(const Ray& r);
    tuple<double, double> intersect(const Ray& r);

    //void addLighting(const Ray & r, double intersection1, double interscction2);

    Point3 getCenter() { return center_; }
    double getRadius() { return radius_; }

    void setRadius(double r) { radius_ = r; }
    
    void setAmbience(double ambiance) { ambience_ = ambiance; }
    double getAmbience() { return ambience_; }

    void setDiffuse(double diffuse) { diffuse_ = diffuse; }
    double getDiffuse() { return diffuse_; }

    void setSpecular(double specular) { specular_ = specular; }
    double getSpecular() { return specular_; }

    void setShininess(double shininess) { shininess_ = shininess; }
    double getShininess() { return shininess_; }

    double applyTexture(Texture texture, Point3 pos);
 

private:
    Point3 center_;
    double radius_ = 0;

    double ambience_ = 1;
    double diffuse_ = 1;
    double specular_ = 1;
    double shininess_ = 1;
};


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