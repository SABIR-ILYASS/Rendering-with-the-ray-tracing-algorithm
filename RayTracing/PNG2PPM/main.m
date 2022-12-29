moon = imread("../moon.png");
moon1 = double(double(moon));
moon2 = double(imresize(moon, 0.5));
moon3 = double(imresize(moon, 0.2));
moon4 = double(imresize(moon, 0.05));

% image2PPM(moon4, "RayTracing", "moon5.ppm");
% image2PPM(moon3, "RayTracing", "moon6.ppm");
image2PPM(moon4, "RayTracing", "moon8.ppm");


%image2PPM(moon3, "RayTracing", "moon3.ppm");
%image2PPM(moon2, "RayTracing", "moon2.ppm");
%image2PPM(moon1, "RayTracing", "moon1.ppm");


