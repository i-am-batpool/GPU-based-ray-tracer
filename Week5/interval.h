#ifndef INTERVAL_H
#define INTERVAL_H

#include "main.h"

class interval {
    public:
        real min, max;
        interval(): min(-infinity), max(infinity) {}
        interval(real min, real max): min(min), max(max) {}

        real size() const{
            return max-min;
        }

        bool contains(real x) const{
            return (min<=x)&&(x<=max); 
        }

        bool surrounds(real x) const{
            return (min<x)&&(x<max);
        }

        real clamp(real x) const{
            if (x<min) return min;
            if (x>max) return max;
            return x;
        }

        static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif