#include "camera.hpp"
#include "canvas.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

void Camera::update_aspect_ratio() {
    aspect_ratio = (double)res[0]/res[1];
}

void Camera::update_axes() {

    std::tie(front,right,up) = get_relative_axes(this->pos.point_at(look_at));
}

void Camera::initialize_values() {
    pixel_size = width/res[0];
    top_left_pixel = offset_local({right,up,front},{-(width-pixel_size)/2,(height-pixel_size)/2,focal_length/36});
}

void Camera::update_size() {
    update_aspect_ratio();
    width = std::min(aspect_ratio,double{1});
    height = std::min(1/aspect_ratio,double{1});
    focus_distance = (look_at-pos).length();
}

Vec3 Camera::get_pixel_local_pos(const int & x, const int & y) {
    return top_left_pixel + offset_local({right,up,vec3_zero},{pixel_size*x,pixel_size*y,0});
}

Vec3 Camera::shoot_ray_from_pixel(const int & x, const int & y) {
    Vec3 start_pixel_pos = get_pixel_local_pos(x,y);

    Vec3 ray_target = pos + start_pixel_pos*focus_distance/(focal_length/36);

    Vec3 ray_origin = pos;

    Vec3 ray_dir = ray_origin.point_at(ray_target);

    Ray pixel_ray = {ray_origin,ray_dir,};

    if (ray_dir.x > 0) {
        return vec3_one;
    } else {
        return vec3_zero;
    }

    // return pixel_ray.dir*2-vec3_one;
}

void Camera::render() {
    update_axes();
    update_size();
    initialize_values();

    std::vector<std::array<int,2>> remaining_pixels = {};

    for (int y=0;y<res[0];y++) {
        for (int x=0;x<res[1];x++) {
            remaining_pixels.push_back({x,y});
        }
    }
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::shuffle(remaining_pixels.begin(), remaining_pixels.end(), gen);
//
//     for (const std::array<int,2> pixel : remaining_pixels) {
//         auto [x,y] = pixel;
//
//         unsigned int seed = y*res[0]+x;
//         std::mt19937 gen(seed);
//
//         Vec3 color = shoot_ray_from_pixel(x,y);
//
//         canvas.put_pixel(color,x,y);
//     }

    for (int y=0;y<res[1];y++) {
        for (int x=0;x<res[0];x++) {
            Vec3 color = (shoot_ray_from_pixel(x,y)+vec3_one)/2;
            canvas.put_pixel(color,x,y);
        }
    }

    std::ofstream file("result.txt");
    file << canvas;
    file.close();

    save_img(canvas, "result.ppm");
}
