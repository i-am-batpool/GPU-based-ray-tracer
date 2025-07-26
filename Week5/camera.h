#ifndef CAMERA_H
#define CAMERA_H
#include "hittable.h"
#include "material.h"

class camera {
    public:
        //image characteristics that should be set ideally by the calling code. But default values have still been set.
        real aspect_ratio=1.0;
        int image_width=100;
        int samples_per_pixel=100;
        int max_depth=10;

        //render function is the only function the caller needs to call after setting the characteristics and configuring the world and the tracing and 
        //generation will happen
        void render(const hittable& world){
            initialize(); //to initialize the camera characteristics.

            //Final rendering not much to see here.
            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            for (int j=0; j<image_height; j++){
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i=0; i<image_width; i++){
                    color pixel_color(0,0,0);
                    for (int _=0; _<samples_per_pixel; _++){
                        ray r = get_ray(i,j);
                        pixel_color=pixel_color+ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_color*pixels_samplescale);
                }
            }

            std::clog << "\rDone.                 \n";
        }
    private:
        int image_height; 
        point3 center; //camera center
        point3 pixel00_loc; //first pixel
        Vec3 pixel_delta_u; //a vector in x direction to go from one pixel to the next
        Vec3 pixel_delta_v; //a vector in y direction to go from one pixel to the next
        real pixels_samplescale;
        
        //to initialize the camera characteristics.
        void initialize(){ 
            //image height calculated using width and aspect ratio.
            image_height=int(image_width/aspect_ratio);
            image_height=(image_height<1) ? 1:image_height;

            //setting camera(center and viewport) characteristics
            auto focal_length = 1.0; //distance between camera and viewport
            auto viewport_height=2.0;
            auto viewport_width=viewport_height * (real(image_width)/image_height);
            center=point3(0,0,0);

            //calculating vectors across horizontal and vertical viewport edges
            auto viewport_u=Vec3(viewport_width,0,0);
            auto viewport_v=Vec3(0,-viewport_height,0);

            //calculating horizontal and vertical pixel to pixel delta vectors
            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/image_height;

            auto viewport_upper_left=center-point3(0,0,focal_length)-viewport_u/2-viewport_v/2;
            pixel00_loc= viewport_upper_left+pixel_delta_u/2+pixel_delta_v/2;

            pixels_samplescale= 1.0/samples_per_pixel;
        }

        color ray_color(const ray& r, int depth, const hittable& world){
            if (depth<=0){ // if bounces too many times then no light received
                return color(0,0,0);
            }
            hit_record rec;
            if (world.hit(r, interval(0.001, infinity), rec)){ //0.001 to fix shadow acne problem,with that it wont end up taking the same point again in precision issues...
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r,rec,attenuation,scattered)){
                    return attenuation*(ray_color(scattered,depth-1,world));
                }
                return color(0,0,0);
            }

            Vec3 unit_direction = r.direction().unit();
            auto a = 0.5*(unit_direction[1]+1.0);
            return color(1.0,1.0,1.0)*(1.0-a)+color(0.5, 0.7, 1.0)*a;
        }

        ray get_ray(int i,int j){
            auto offset=square_randompt();
            auto pixel_sample = pixel00_loc+(pixel_delta_u*(i+offset[0]))+(pixel_delta_v*(j+offset[1]));
            return ray(center, pixel_sample-center);
        }

        Vec3 square_randompt() const{
            return Vec3(random_real()-0.5, random_real()-0.5, 0);
        }
};
#endif