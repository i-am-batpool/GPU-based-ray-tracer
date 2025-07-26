#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ std usings
using std::shared_ptr;
using std::make_shared;
using real=double;

//constants
const real infinity = std::numeric_limits<real>::infinity();
const real pi=3.1415926535897932385;

//utility functions
inline real degrees_to_radians(real degrees){
    return (degrees * pi)/180.0;
}

inline real random_real(){ //generates random real in range [0,1)
    return std::rand()/(RAND_MAX+1.0);
}

inline real random_real(real min, real max){
    return min+(max-min)*random_real();
}

//common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif