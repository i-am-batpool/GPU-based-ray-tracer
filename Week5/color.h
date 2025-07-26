#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using color=Vec3;

inline real linear_to_gamma(real lin_component){
    if (lin_component>0){
        return std::sqrt(lin_component);
    }
    return 0;
}

void write_color(std::ostream& out, const color& pixel_color){
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    r=linear_to_gamma(r);
    g=linear_to_gamma(g);
    b=linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif