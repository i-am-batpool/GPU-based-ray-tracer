#include "main.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


color ray_color(const ray& r, const hittable& world){
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)){
        return (rec.normal + color(1,1,1))*0.5;
    }

    Vec3 unit_direction = r.direction().unit();
    auto a = 0.5*(unit_direction[1]+1.0);
    return color(1.0,1.0,1.0)*(1.0-a)+color(0.5, 0.7, 1.0)*a;
}

int main(){
    //setting image characteristics
    auto aspect_ratio = 16.0/9.0;
    int image_width=400;
    int image_height=int(image_width/aspect_ratio);
    image_height=(image_height<1) ? 1:image_height; //calculating and ensuring image_height is atleast 1...cause there shud be 1 pixel atleast

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); //sphere in between
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100)); //ground

    //setting camera(center and viewport) characteristics
    auto focal_length = 1.0; //distance between camera and viewport
    auto viewport_height=2.0;
    auto viewport_width=viewport_height * (float(image_width)/image_height);
    auto camera_center=point3(0,0,0);

    //calculating vectors across horizontal and vertical viewport edges
    auto viewport_u=Vec3(viewport_width,0,0);
    auto viewport_v=Vec3(0,-viewport_height,0);

    //calculating horizontal and vertical pixel to pixel delta vectors
    auto pixel_delta_u = viewport_u/image_width;
    auto pixel_delta_v = viewport_v/image_height;

    //calculate position of upper left pixel
    auto viewport_upper_left=camera_center-point3(0,0,focal_length)-viewport_u/2-viewport_v/2;
    auto pixel00_loc= viewport_upper_left+pixel_delta_u/2+pixel_delta_v/2;
    
    //Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j=0; j<image_height; j++){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i=0; i<image_width; i++){
            auto pixel_center=pixel00_loc+(pixel_delta_u*i)+(pixel_delta_v*j);
            auto ray_direction=pixel_center-camera_center;
            ray r(camera_center, ray_direction);
            color pixel_color= ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
