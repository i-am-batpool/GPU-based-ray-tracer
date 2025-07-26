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

class dielectric : public material {
    private:
        real refractive_index;

        static double reflectance(double cosine, double refraction_index) {//Schlick's approximation 
            auto r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1 - cosine),5);
        }

    public:
        dielectric(double refractive_index): refractive_index(refractive_index) {}

        bool scatter(const ray& in, const hit_record& rec, color& attenuation, ray& scattered) const override{
            attenuation=color(1.0,1.0,1.0);
            Vec3 scatter_dir;

            real ref = rec.front_face?refractive_index:1.0/refractive_index;

            real cos_theta = std::fmin(-in.direction().unit().dot(rec.normal), 1.0);
            if (reflectance(cos_theta,ref)>random_real()){
                scatter_dir = in.direction().reflect(rec.normal);
            } else scatter_dir = in.direction().refract(rec.normal, ref);
            
            scattered=ray(rec.point, scatter_dir);
            return true;
        }
};

#endif