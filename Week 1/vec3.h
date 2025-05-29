#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <stdexcept>


class Vec3{
    float e[3];
    public:
        //constuctors
        Vec3() : e{0,0,0} {}
        Vec3(float x, float y, float z) : e{x,y,z} {}

        //operator overloads
        Vec3 operator+(const Vec3& other) const{
            return Vec3(e[0]+other.e[0], e[1]+other.e[1], e[2]+other.e[2]);
        }
        Vec3 operator-(const Vec3& other) const{
            return Vec3(e[0]-other.e[0], e[1]-other.e[1], e[2]-other.e[2]);
        }
        Vec3 operator*(const float& mul) const{
            return Vec3(mul*e[0], mul*e[1], mul*e[2]);
        }
        Vec3 operator/(const float& div) const{
            if (div==0){
                throw std::runtime_error("Division by zero");
            }
            return Vec3(e[0]/div, e[1]/div, e[2]/div);
        }
        Vec3 operator-() const{
            return Vec3(-e[0],-e[1],-e[2]);
        }
        float operator[](int i) const{
            return e[i];
        }

        //methods
        float length() const{
            return std::sqrt((e[0]*e[0])+(e[1]*e[1])+(e[2]*e[2]));
        }
        Vec3 unit() const{
            float len = length();
            if (len==0){
                throw std::runtime_error("Cannot normalize zero vector");
            }
            return Vec3(e[0]/len, e[1]/len, e[2]/len);
        }
        float dot(const Vec3& other) const{
            return ((e[0]*other.e[0])+(e[1]*other.e[1])+(e[2]*other.e[2]));
        }
        Vec3 cross(const Vec3& other) const{
            return Vec3((e[1]*other.e[2])-(e[2]*other.e[1]), (e[2]*other.e[0])-(e[0]*other.e[2]), (e[0]*other.e[1])-(e[1]*other.e[0]));
        }
        Vec3 reflect(const Vec3& normal) const{
            Vec3 uv = (*this).unit();
            Vec3 norm = normal.unit();
            return (uv - norm*(uv.dot(norm))*2);
        }
        Vec3 refract(const Vec3& normal, float refractive_index) const{
            Vec3 norm = normal.unit();
            Vec3 uv = (*this).unit();

            float cos_theta = fmin(-uv.dot(norm), 1.0f);
            float sin2_theta = 1.0f - cos_theta * cos_theta;
            if (sin2_theta > (refractive_index * refractive_index)) { //total internal reflection
                return reflect(norm); 
            }

            Vec3 rper = (uv+(norm*(-uv.dot(norm))))/refractive_index;
            Vec3 rpar = -norm*std::sqrt(1-((rper.length())*(rper.length())));
            return (rper+rpar);
        }
};

#endif