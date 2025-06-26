#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
    private:
        point3 centre;
        float radius;
    public:
        sphere(const point3& centre, float radius): centre(centre), radius(std::fmax(radius,0)) {}
        
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            Vec3 oc = centre - r.origin();
            auto a = r.direction().dot(r.direction());
            auto h = oc.dot(r.direction());
            auto c = oc.dot(oc) - radius*radius;
            auto discriminant = h*h - a*c;
            
            if (discriminant<0){
                return false;
            } 
            auto sqrdisc = std::sqrt(discriminant);
            auto root = (h - sqrdisc)/a;
            if (!ray_t.surrounds(root)){
                root = (h+sqrdisc)/a;
                if (!ray_t.surrounds(root)) return false;
            }

            rec.t=root;
            rec.point=r.at(root);
            Vec3 outward_normal=(rec.point-centre)/radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
};

#endif