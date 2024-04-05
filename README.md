# Ray Tracing Project

This project implements a simple ray tracing engine using C++ programming language. Ray tracing is a technique for rendering 3D images that simulates the behavior of light by tracing rays from the camera into the virtual scene.

## Features

The ray tracing engine supports the following features:

- **Sphere Intersection**: The engine can detect intersections between rays and spheres in the scene. The equation for ray-sphere intersection is given by:

  ![equation](https://latex.codecogs.com/png.latex?\inline&space;\bg_white&space;\text{ray}&space;=&space;\text{origin}&space;+&space;t&space;\cdot&space;\text{direction})

  Where `ray` is the intersection point, `origin` is the origin of the ray, `t` is the distance along the ray, and `direction` is the direction of the ray.

- **Shading**: The engine calculates the shading of objects based on the lighting in the scene. The shading equation combines the ambient, diffuse, and specular components to determine the final color of a pixel.

- **Reflection**: The engine supports reflection by recursively tracing reflected rays. The reflection equation is given by:

  ![equation](https://latex.codecogs.com/png.latex?\inline&space;\bg_white&space;\text{reflected}&space;=&space;\text{direction}&space;-&space;2&space;\cdot&space;\text{normal}&space;\cdot&space;(\text{direction}&space;\cdot&space;\text{normal}))

  Where `reflected` is the reflected ray direction, `direction` is the incident ray direction, and `normal` is the surface normal.

## Usage

To use the ray tracing engine, follow these steps:

1. Clone the repository:

   ```
   https://github.com/SABIR-ILYASS/Rendering-with-the-ray-tracing-algorithm.git
   ```

2. Compile the code using a C++ compiler. For example:

   ```
   g++ ray_tracing.cpp -o ray_tracing
   ```

3. Run the compiled program:

   ```
   ./ray_tracing
   ```

   This will generate an image based on the scene description specified in the code.

## Contribution

Contributions to this ray tracing project are welcome. If you find any issues or have ideas for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

For more information on ray tracing, refer to the following resources:

- [Wikipedia - Ray tracing (graphics)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
- [Scratchapixel - Introduction to Ray Tracing](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing)
