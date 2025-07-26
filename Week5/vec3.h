#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <stdexcept>


class Vec3{
    real e[3];
    public:
        //constuctors
        Vec3() : e{0,0,0} {}
        Vec3(real x, real y, real z) : e{x,y,z} {}

        //operator overloads
        Vec3 operator+(const Vec3& other) const{
            return Vec3(e[0]+other.e[0], e[1]+other.e[1], e[2]+other.e[2]);
        }
        Vec3 operator-(const Vec3& other) const{
            return Vec3(e[0]-other.e[0], e[1]-other.e[1], e[2]-other.e[2]);
        }
        Vec3 operator*(const real& mul) const{
            return Vec3(mul*e[0], mul*e[1], mul*e[2]);
        }
        Vec3 operator*(const Vec3& mul) const{
            return Vec3(mul[0]*e[0],mul[1]*e[1],mul[2]*e[2]);
        }
        Vec3 operator/(const real& div) const{
            if (div==0){
                throw std::runtime_error("Division by zero");
            }
            return Vec3(e[0]/div, e[1]/div, e[2]/div);
        }
        Vec3 operator-() const{
            return Vec3(-e[0],-e[1],-e[2]);
        }
        real operator[](int i) const{
            return e[i];
        }

        //methods
        real length() const{
            return std::sqrt((e[0]*e[0])+(e[1]*e[1])+(e[2]*e[2]));
        }
        Vec3 unit() const{
            real len = length();
            if (len==0){
                throw std::runtime_error("Cannot normalize zero vector");
            }
            return Vec3(e[0]/len, e[1]/len, e[2]/len);
        }
        real dot(const Vec3& other) const{
            return ((e[0]*other.e[0])+(e[1]*other.e[1])+(e[2]*other.e[2]));
        }
        Vec3 cross(const Vec3& other) const{
            return Vec3((e[1]*other.e[2])-(e[2]*other.e[1]), (e[2]*other.e[0])-(e[0]*other.e[2]), (e[0]*other.e[1])-(e[1]*other.e[0]));
        }
        Vec3 reflect(const Vec3& normal) const{
            Vec3 norm=normal;
            //Vec3 norm = normal.unit(); will always use normal as unit vector only. Pass also that way. In case it turns out thats not the case later uncomment this. This is an expensive operation.
            return ((*this) - normal*((*this).dot(normal))*2);
        }
        Vec3 refract(const Vec3& normal, real refractive_index) const{
            Vec3 norm = normal;
            //Vec3 norm = normal.unit(); will always use normal as unit vector only. Pass also that way. In case it turns out thats not the case later uncomment this. This is an expensive operation.
            Vec3 uv = (*this).unit();

            real cos_theta = fmin(-uv.dot(norm), 1.0f);
            real sin2_theta = 1.0f - cos_theta * cos_theta;
            if (sin2_theta > (refractive_index * refractive_index)) { //total internal reflection
                return reflect(norm); 
            }

            Vec3 rper = (uv+(norm*(-uv.dot(norm))))/refractive_index;
            Vec3 rpar = -norm*std::sqrt(1-((rper.length())*(rper.length())));
            return (rper+rpar);
        }

        // random vector generators
        static Vec3 random_vector(){
            return Vec3(random_real(), random_real(), random_real());
        }

        static Vec3 random_vector(real min, real max){
            return Vec3(random_real(min,max), random_real(min, max), random_real(min, max));
        }

        static inline Vec3 random_unit_vector(){
            while (true){
                auto p = Vec3::random_vector(-1,1);
                if (p.length()<1){
                    try{
                        return p.unit();
                    } catch (...){}
                }
            }
        }

        static inline Vec3 random_on_hemisphere(const Vec3& normal){
            Vec3 unit = random_unit_vector();
            if (normal.dot(unit)<0){
                unit=-unit;
            }
            return unit;
        }

        bool near_zero() const{
            real s = 1e-8;
            return ((abs(e[0])<s) && (abs(e[1])<s) && (abs(e[2])<s));
        }
};

using point3=Vec3; //in order to differentiate when we mean to represent the position vector of a point. Just an alias of Vec3 class. Useful in Week 2.

#endif