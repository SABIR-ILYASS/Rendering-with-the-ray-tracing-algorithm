#include "Color.h"
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "ImagePPM.h"
// #include "SphereEnglobant.h"
#include "Triangle.h"

#include <iostream>
#include <tuple>
#include <vector>

#include <sstream>
#include <string>


using namespace std;


void figure1() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // add sphere
    Sphere sphere = Sphere(Point3(0, 0, -1), 0.5);

    // create Image
    string pathOut = "../images/";
    ImagePPM image1 = ImagePPM(image_width, image_height, pathOut, 1);

    for (int j = image_height - 1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {

            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color;

            if (sphere.isIntersect(r))
                pixel_color = Color(1.0, 1.0, 1.0);
            else 
            {
                pixel_color = Color(0.0, 0.0, 0.0);
            }

            write_color(pixel_color, image1);
        }
    }
    image1.setPixeltoImage();

    cerr << "\nDone.\n";

}

void figure2() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // add spheres
    Sphere sphere1 = Sphere(Point3(0, 0, -1), 0.5);
    auto color1 = Color(1.0, 0.0, 0.0);

    Sphere sphere2 = Sphere(Point3(0, 0.5, -1), 0.4);
    auto color2 = Color(0.0, 1.0, 0.0);

    Sphere sphere3 = Sphere(Point3(0.5, -0.5, -1.5), 0.8);
    auto color3 = Color(1.0, 1.0, 1.0);

    Sphere sphere4 = Sphere(Point3(-1, 0.5, -1), 0.25);
    auto color4 = Color(0.0, 0.0, 1.0);

    // create Image
    string pathOut = "../images/";
    ImagePPM image2 = ImagePPM(image_width, image_height, pathOut, 2);

    for (int j = image_height - 1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);

            // intersections
            auto intersection1 = sphere1.intersect(r);
            double PImin1 = std::get<0>(intersection1);
            double PImax1 = std::get<1>(intersection1);

            auto intersection2 = sphere2.intersect(r);
            double PImin2 = std::get<0>(intersection2);
            double PImax2 = std::get<1>(intersection2);

            auto intersection3 = sphere3.intersect(r);
            double PImin3 = std::get<0>(intersection3);
            double PImax3 = std::get<1>(intersection3);

            auto intersection4 = sphere4.intersect(r);
            double PImin4 = std::get<0>(intersection4);
            double PImax4 = std::get<1>(intersection4);

            Color pixel_color;

            if (PImax1 == -1 && PImax2 == -1 && PImax3 == -1 && PImax4 == -1)
                pixel_color =  Color(0.0, 0.0, 0.0);

            else {
                double tmax = std::max(PImax1, std::max(PImax2, std::max(PImax3, PImax4)));

                if (tmax == PImax1)
                    pixel_color = color1;
                else if (tmax == PImax2)
                    pixel_color = color2;
                else if (tmax == PImax3)
                    pixel_color = color3;
                else
                    pixel_color = color4;
            }
            write_color(pixel_color, image2);
        }
    }
    image2.setPixeltoImage();

    cerr << "\nDone.\n";

}


void figure3()
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // add sphere
    Sphere sphere1 = Sphere(Point3(0, 0, -1), 0.5);

    // light of sphere
    sphere1.setAmbience(0.2);
    sphere1.setDiffuse(0.7);
    sphere1.setSpecular(1.9);
    sphere1.setShininess(20.0);

    double ambience = sphere1.getAmbience();
    double diffuse = sphere1.getDiffuse();
    double specular = sphere1.getSpecular();
    double shininess = sphere1.getShininess();

    // light model
    Vec3 posLight = Vec3(0.5, 1, 0);
    Color lightColor = Color(1.0, 1.0, 1.0);
    auto colorSphere = Color(1.0, 0.0, 0.0);

    // create Image
    string pathOut = "../images/";
    ImagePPM image3 = ImagePPM(image_width, image_height, pathOut, 3);

    for (int j = image_height - 1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            
            auto intersection1 = sphere1.intersect(r);
            double PImin1 = std::get<0>(intersection1);
            double PImax1 = std::get<1>(intersection1);
            
            Color pixel_color;

            if (PImax1 == -1)
                pixel_color = Color(0.0, 0.0, 0.0);

            else {
                Point3 intersection = r.at(PImin1);
                Vec3 L = posLight - intersection;
                Vec3 rayonLight = unit_vector(L);
                Vec3 normal = unit_vector(intersection - sphere1.getCenter());

                double CosRayInter = dot(rayonLight, normal);

                double coeff = std::min(1., std::max(0., CosRayInter));

                Color ambientLight = ambience * colorSphere;
                Color diffuseLight = diffuse * std::max(coeff, 0.) * colorSphere;
                double shin = pow(std::max(-dot(r.direction(), reflection(rayonLight, normal)), 0.), shininess);
                Color specularLight = specular * shin * colorSphere;

                pixel_color = ambientLight + diffuseLight + specularLight;
            }

            write_color(pixel_color, image3);
        }
    }
    image3.setPixeltoImage();

    cerr << "\nDone.\n";

}




void figure4()
{
    
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // add triangle
    Point3 P1 = Point3(1, -0.5, -1);
    Point3 P2 = Point3(-1, -0.5, -1);
    Point3 P3 = Point3(0, 0.5, -1);

    Triangle triangle = Triangle(P1, P2, P3);

    // create Image
    string pathOut = "../images/";
    ImagePPM image4 = ImagePPM(image_width, image_height, pathOut, 4);

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
          
            double atInter = triangle.intersection(r);

            Color pixel_color;

            if (atInter > 0)
                pixel_color = Color(1., 1., 1.);
            else
            {
                pixel_color = Color(0.0, 0.0, 0.0);
            }
                
            write_color(pixel_color, image4);
        }
    }
    image4.setPixeltoImage();

    cerr << "\nDone.\n";
    

}


void figure5()
{
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // create Image
    string pathOut = "../images/";
    ImagePPM image5 = ImagePPM(image_width, image_height, pathOut, 5);

    Texture * texture = new Texture("../PNG2PPM/RayTracing/moon1.ppm");

    Sphere sphere1 = Sphere(Point3(0, 0, -1), 0.5);
    Color pixel_color;

    // light of sphere
    sphere1.setAmbience(0.1);
    sphere1.setDiffuse(1.0);
    //sphere1.setShininess(20.0);

    double ambience = sphere1.getAmbience();
    double diffuse = sphere1.getDiffuse();
    double specular = sphere1.getSpecular();

    // light model
    Vec3 posLight = Vec3(0.5, 1, 0);
    Color lightColor = Color(1.0, 1.0, 1.0);

    for (int j = image_height - 1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
  
            auto intersection1 = sphere1.intersect(r);
            double PImin1 = std::get<0>(intersection1);
            double PImax1 = std::get<1>(intersection1);


            if (PImax1 == -1)
                pixel_color = Color(0.0, 0.0, 0.0);

            else {
                Point3 intersection = r.at(PImin1);
                double color = sphere1.applyTexture(* texture, intersection);
                Color colorSphere = Color(color, color, color);

                Vec3 L = posLight - intersection;
                Vec3 rayonLight = unit_vector(L);
                Vec3 normal = unit_vector(intersection - sphere1.getCenter());

                double CosRayInter = dot(rayonLight, normal);

                double coeff = std::min(1., std::max(0., CosRayInter));

                Color ambientLight = ambience * colorSphere;
                Color diffuseLight = diffuse * std::max(coeff, 0.) * colorSphere;

                pixel_color = ambientLight + diffuseLight;


            }

            write_color(pixel_color, image5);
        }
    }
    image5.setPixeltoImage();

    delete texture;

    cerr << "\nDone.\n";

}

int main() {

    int input;
    cerr << "input the number of figure: 1, 2, 3, 4 or 5." << endl;

    cin >> input;

    switch (input)
    {
    case 1:
        figure1();
        break;

    case 2:
        figure2();
        break;

    case 3:
        figure3();
        break;

    case 4:
        figure4();
        break;

    case 5:
        figure5();
        break;

    default:
        cerr << "Please inter a number between 1 and 5." << flush;
        break;


    }
 
    
}
