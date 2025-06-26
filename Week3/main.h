#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ std usings
using std::shared_ptr;
using std::make_shared;

//constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi=3.1415926535897932385;

//utility functions
inline float degrees_to_radians(float degrees){
    return (degrees * pi)/180.0;
}

//common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif