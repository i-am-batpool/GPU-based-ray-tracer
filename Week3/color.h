#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color=Vec3;

void write_color(std::ostream& out, const color& pixel_color){
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    int rbyte=int(255.999*r);
    int gbyte=int(255.999*g);
    int bbyte=int(255.999*b);

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif