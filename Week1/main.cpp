#include <iostream>
#include "vec3.h"

using std::cout;

int main(){

    int width=256;
    int height=256;

    cout << "P3\n" << width << " " << height << "\n255\n";

    for (int i=0; i<width; i++){
        std::clog << "\rScanlines remaining: " << (height - i) << ' ' << std::flush;  //because of carriage return and flushing, the output will keep on updating rather than new lines everytime
        for (int j=0; j<height; j++){
            double r = double(i)/(width-1);
            double g = double(j)/(height-1);
            double b = 0;

            int ir = int(255.999*r);
            int ig = int(255.999*g);
            int ib = int(255.999*b);

            cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::clog << "\rDone.                 \n";
}



//written for the purpose of testing Vec3 class:
/* float ax,ay,az,bx,by,bz,u;
    std::cout << "Enter A ";
    std::cin >> ax >> ay >> az;
    std::cout << "\nEnter B ";
    std::cin >> bx >> by >> bz;
    std::cout << "\nEnter refrax ";
    std::cin >> u;
    Vec3 A(ax,ay,az);
    Vec3 B(bx,by,bz);
    std::cout << "\nA+B ";
    std::cout << (A+B)[0] << " " << (A+B)[1] << " " << (A+B)[2];
    std::cout << "\nA-B ";
    std::cout << (A-B)[0] << " " << (A-B)[1] << " " << (A-B)[2];
    std::cout << "\nA dot B ";
    std::cout << (A.dot(B));
    std::cout << "\nA cross B ";
    std::cout << (A.cross(B))[0] << " " << (A.cross(B))[1] << " " << (A.cross(B))[2];
    std::cout << "\nLength of A ";
    std::cout << A.length();
    std::cout << "\nUnit of A ";
    std::cout << (A.unit())[0] << " " << (A.unit())[1] << " " << (A.unit())[2];
    std::cout << "\nReflect A about N ";
    std::cout << (A.reflect(B))[0] << " " << (A.reflect(B))[1] << " " << (A.reflect(B))[2];
    std::cout << "\nRefraction A about N ";
    std::cout << (A.refract(B, u))[0] << " " << (A.refract(B, u))[1] << " " << (A.refract(B, u))[2]; */