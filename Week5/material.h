#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material{
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const{
            return false;
        }
};

class lambertian : public material {
    private:
        color albedo;
    public:
        lambertian(const color& albedo): albedo(albedo){}

        bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override{
            auto scatter_direction = rec.normal + Vec3::random_unit_vector();
            attenuation=albedo;

            if (scatter_direction.near_zero()) scatter_direction=rec.normal;

            scattered=ray(rec.point, scatter_direction);
            return true;
        }
};

class metal : public material {
    private:
        color albedo;
        real fuzz;
    public:
        metal(const color& albedo, real fuzz): albedo(albedo), fuzz(fuzz<1 ? fuzz:1) {}

        bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override{
            auto reflect_direction = in.direction().reflect(rec.normal);
            auto scatter_direction = reflect_direction.unit()+Vec3::random_unit_vector()*fuzz;
            attenuation = albedo;
            scattered = ray(rec.point, scatter_direction);
            return (scatter_direction.dot(rec.normal) >0);
        }
};

#endif