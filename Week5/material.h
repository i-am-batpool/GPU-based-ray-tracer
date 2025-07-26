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
    public:
        metal(const color& albedo): albedo(albedo) {}

        bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override{
            auto scatter_direction = in.direction().reflect(rec.normal);
            attenuation = albedo;
            scattered = ray(rec.point, scatter_direction);
            return true;
        }
};

#endif