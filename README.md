# Image Synthesis Project

Author: SABIR Ilyass

In this project, we aim to generate synthetic images by rendering 3D scenes. The camera is positioned at (0, 0, 0) in the space coordinate system, and the viewing plane is set at z = -1.

We have utilized and modified the following code files throughout the project: `Vec3.h`, `Color.h`, and `Ray.h`. To automate the creation of PPM images, we have implemented a class called `ImagePPM`. This class is responsible for creating an image.ppm file in a specified directory and adding pixel values to the image. The components developed personally include: the `ImagePPM` class, the `ListSphere` class, the `Triangle` class, the `Texture` class, the `applyTexture` method in the `Sphere` class, along with other methods for applying 3D rendering to spheres (refer to Part 3), and the `inline reflection` method in the `Vec3` class.

After executing the code, to generate Figure (i), you need to enter the corresponding number 'i' where i belongs to the set {1, 2, 3, 4, 5, 6}.

## Representation of a Sphere

The initial objective of the project is to render a black and white image, where the white areas correspond to the location of the sphere as seen from the camera in the scene. To achieve this, we test for ray/sphere intersections. We define a ray 'r' as a line with origin 'Or' and direction 'Dr'. A point 'P' belongs to 'r' if and only if there exists a value 't' such that P = Or + tDr. A sphere 'S' is defined by its center 'Cs' and radius 'Rs'. A point 'P' belongs to 'S' if and only if the equation |P - Cs| = Rs holds, where |.| denotes the Euclidean norm in R^3.

To determine if there is an intersection between the ray 'r' and the sphere 'S', we check if the equation 'kOr + tDr - Cs| = Rs' has any solutions. By simplifying this equation, we obtain the quadratic equation 'kOr + tDr - Cs|^2 - Rs^2 = 0'. Thus, the intersection between the ray and the sphere is determined by solving this quadratic equation. For real solutions to exist, the discriminant of the equation should be greater than zero.

The resulting image after executing the code is shown in Figure 1.

![Figure 1: Representation of a sphere](link_to_image_1)

## Representation of Multiple Spheres

The second part of the project involves displaying multiple spheres in the scene. However, it is not enough to determine only ray/sphere intersections; we also need to know the intersection points. Based on equation (2), if the equation has real solutions, we calculate the intersection points.

The solutions of equation (2) are given by t- and t+, where t- and t+ are determined as follows:

t- = (hDr | Or - Cs i - hDr | Or - Cr i^2 - (|Or - Cr|^2 - Rs^2) |Dr|^2) / |Dr|^2

t+ = (hDr | Or - Cs i + hDr | Or - Cr i^2 - (|Or - Cr|^2 - Rs^2) |Dr|^2) / |Dr|^2

The solution of interest is the one that gives the intersection point closest to the camera. For each sphere Si (Csi, Rsi), where Csi

 is the center and Rsi is the radius, we find the corresponding t-value using equations (3) and (4) and determine the closest intersection point P. If the ray does not intersect any sphere, we color the pixel black.

The resulting image after executing the code is shown in Figure 2.

![Figure 2: Representation of multiple spheres](link_to_image_2)

## Implementation of the Phong Model

The Phong model provides a way to calculate the reflection of light from a surface point. It is composed of three components: the ambient, diffuse, and specular reflections. The ambient reflection represents the light that is scattered uniformly in all directions. The diffuse reflection accounts for the light that is scattered in all directions due to the surface roughness. The specular reflection represents the light that is reflected in a particular direction due to the smoothness of the surface.

To implement the Phong model, we need to calculate the normal vector N at the intersection point P and the vector L from the intersection point to the light source. The normal vector N can be calculated as N = (P - Cs) / |P - Cs|, where Cs is the center of the sphere. The vector L can be calculated as L = Ls - P, where Ls is the position of the light source.

Using the normal vector N and the vector L, we can calculate the ambient, diffuse, and specular reflections at the intersection point. The resulting color at the intersection point is the sum of these three components.

The resulting image after executing the code is shown in Figure 3.

![Figure 3: Implementation of the Phong model](link_to_image_3)

## Bounding Sphere Hierarchy

To improve the efficiency of ray/sphere intersection tests, we can use a bounding sphere hierarchy. The idea is to create a hierarchy of bounding spheres that enclose groups of spheres. This allows us to quickly discard groups of spheres that do not intersect with the ray, reducing the number of intersection tests.

The bounding sphere hierarchy is constructed using a top-down approach. We start with all spheres and recursively partition them into groups until each group contains a small number of spheres. Each group is enclosed by a bounding sphere that represents the union of all spheres in the group.

When testing for ray/sphere intersections, we first check if the ray intersects the bounding sphere of the top-level group. If it does not, we can immediately discard the group and its subgroups. If it does, we recursively test for intersections with the subgroups until we find the sphere that is closest to the camera.

The resulting image after executing the code is shown in Figure 4.

![Figure 4: Bounding sphere hierarchy](link_to_image_4)

## Texturing Spheres

In this part of the project, we add textures to the spheres. Textures are images that can be mapped onto the surfaces of objects to provide details and patterns. To apply a texture to a sphere, we use the concept of spherical coordinates. Each point on the sphere is represented by its spherical coordinates (θ, φ), where θ is the azimuthal angle and φ is the polar angle.

We map the spherical coordinates (θ, φ) to the texture image coordinates (u, v) using the equations:

u = (θ + π) / (2π)

v = φ / π

We then sample the texture image at the coordinates (u, v) to obtain the color of the point on the sphere's surface.

The resulting image after executing the code is shown in Figure 5.

![Figure 5: Texturing spheres](link_to_image_5)

## Rendering Triangle Meshes

In this part of the project, we render triangle meshes using the ray-triangle intersection test. A triangle is defined by its three

 vertices (V1, V2, V3). Given a ray and a triangle, we need to determine if and where the ray intersects the triangle.

To test for ray/triangle intersections, we first calculate the normal vector N of the triangle using the cross product: N = (V2 - V1) x (V3 - V1). We then calculate the determinant D using the dot product: D = (V1 - Or) · N, where Or is the origin of the ray.

If the determinant D is close to zero, the ray is parallel to the triangle and does not intersect it. Otherwise, we calculate the barycentric coordinates (β, γ) using the equations:

β = ((Or - V2) x (V3 - V2)) · N / ((V1 - V2) x (V3 - V2)) · N

γ = ((Or - V3) x (V1 - V3)) · N / ((V1 - V2) x (V3 - V2)) · N

If β and γ are both between 0 and 1, and β + γ is less than or equal to 1, the ray intersects the triangle. We can then calculate the intersection point P using the equation P = Or + tDr, where t is the distance from the origin of the ray to the intersection point.

The resulting image after executing the code is shown in Figure 6.

![Figure 6: Rendering triangle meshes](link_to_image_6)

## Conclusion

In this project, we have implemented various techniques for image synthesis by rendering 3D scenes. We started with the representation of spheres and expanded to multiple spheres, the Phong model, bounding sphere hierarchy, texturing spheres, and rendering triangle meshes. Each part added more complexity and realism to the rendered images.

The techniques covered in this project are fundamental in computer graphics and provide a solid foundation for further exploration and development in the field. By understanding and implementing these techniques, we can create realistic and visually appealing images and animations.

Feel free to explore the code and experiment with different scenes, materials, and lighting conditions to further enhance the image synthesis capabilities.
