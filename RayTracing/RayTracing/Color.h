#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ImagePPM.h"

#include <iostream>

void write_color(Color pixel_color, ImagePPM& image) {
    // Write the translated [0,255] value of each color component.
    int colorX = std::min(255, std::max(0, static_cast<int>(255.999 * pixel_color.x())));
    int colorY = std::min(255, std::max(0, static_cast<int>(255.999 * pixel_color.y())));
    int colorZ = std::min(255, std::max(0, static_cast<int>(255.999 * pixel_color.z())));


    image.setNextPixel(colorX, colorY, colorZ);

}

#endif
