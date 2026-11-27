#pragma once

#include "canvas.hpp"
#include "vec3.hpp"
#include <array>
#include <iosfwd>


struct Camera {
    Vec3 pos,look_at;
    std::array<int,2> res;
    double focal_length;

    Camera(Vec3 pos,Vec3 look_at,std::array<int,2> res,double focal_length):
    pos(pos),look_at(look_at),res(res),focal_length(focal_length)
    {}

    Vec3 front,right,up;

    double width,height,aspect_ratio;

    double pixel_size,pixel_pos;

    Canvas canvas = Canvas(res[0],res[1]);

    Vec3 top_left_pixel;

    double focus_distance;

    void update_aspect_ratio();
    void update_axes();
    void initialize_values();
    void update_size();
    Vec3 get_pixel_local_pos(const int &, const int &);
    Vec3 shoot_ray_from_pixel(const int &, const int &);
    void render();

};
