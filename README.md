# Rendering-with-the-ray-tracing-algorithm
# 3D Reconstruction in Computerized Tomography

This project aims to perform 3D reconstruction in computerized tomography. It involves synthesizing images and implementing various algorithms for rendering 3D objects.

## Author

- Name: SABIR Ilyass

## Project Overview

In this project, the camera is positioned at coordinates (0, 0, 0) in the spatial reference frame, and the viewing scene is in the plane defined by the equation z = -1. The project utilizes the following code files: `Vec3.h`, `Color.h`, and `Ray.h`, which have been modified during the project's progress.

To automate the creation of .ppm images, an `ImagePPM` class has been implemented. This class is responsible for creating an image.ppm file in a specified directory and adding pixel values to that image. Personally developed components include the `ImagePPM` class, the `ListSphere` class, the `Triangle` class, the `Texture` class, the `applyTexture` method in the `Sphere` class (along with other methods for 3D rendering of spheres), and the `inline reflection` method in the `Vec3` class.

After executing the code, to generate a specific figure, the corresponding number (1, 2, 3, 4, 5, 6) needs to be entered.

## 1. Representation of a Sphere

The initial objective of the project is to render a black and white image where the white area corresponds to the location of the sphere as seen in the scene from the camera's perspective. To achieve this, the code checks for intersections between rays and spheres. By utilizing the equation of a ray, it is determined if a point lies on the ray by solving an equation. The intersection between a ray `r` and a sphere `S` occurs if there exists `t` such that `|P - Cs| = Rs`, where `P` is a point on the ray and `Cs` and `Rs` are the center and radius of the sphere `S`, respectively. The problem can be translated into solving the equation `|Or + tDr - Cs| = Rs`, where `Or` is the origin of the ray and `Dr` is the direction of the ray. The resulting equation is a trinomial equation.

The figure below shows the representation of a sphere obtained after executing the code (figure1()).

![Figure 1: Representation of a sphere](1.png)

## 2. Representation of Multiple Spheres

The objective of this part is to display multiple spheres in the scene. It is necessary to determine not only if there is an intersection between a ray and a sphere but also the points of intersection. By solving the equation obtained previously, multiple intersection points are calculated for a family of spheres. The solution of interest is the one that gives the intersection point closest to the camera. The sphere that is closest to the camera is determined, and its color is assigned to the corresponding intersection point.

The figure below shows the representation of multiple spheres obtained after executing the code (figure2()).

![Figure 2: Representation of multiple spheres](e2.png)

## 3. Adding 3D Rendering to Spheres (Phong Model)

In this part, the 3D rendering is added to spheres using the Phong reflection model. The colors for ambient, diffuse, and specular components are calculated. Ambient color is obtained by multiplying the color of the sphere by an ambient coefficient. Diffuse and specular colors depend on the color of the light source and the intersection point of the ray and the sphere. The diffuse color is calculated using the Lambertian reflection model, while the specular color is
