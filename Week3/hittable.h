#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

class hit_record{
    public:
        point3 point;
        Vec3 normal;
        float t;
        bool front_face;

        void set_face_normal(const ray& r, const Vec3& outward_normal){
            //setting the hit record normal vector
            // outward_normal is assumed to have unit length
            front_face=outward_normal.dot(r.direction())<0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable{
    public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif