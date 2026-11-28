#pragma once

#include "canvas.hpp"
#include "scene.hpp"
#include "vec3.hpp"
#include <array>
#include <iosfwd>


struct Camera {
    Vec3 pos,look_at;
    std::array<int,2> res;
    double focal_length;
    int max_bounces;
    Scene scene;

    Camera(
        Vec3 pos,
        Vec3 look_at,
        std::array<int,2> res,
        double focal_length,
        int max_bounces,
        Scene scene
    ):
        pos(pos),
        look_at(look_at),
        res(res),
        focal_length(focal_length),
        max_bounces(max_bounces),
        scene(scene)
    {}

    Vec3 front = vec3_zero;
    Vec3 right = vec3_zero;
    Vec3 up = vec3_zero;

    double width,height,aspect_ratio;

    double pixel_size,pixel_pos;

    Canvas canvas = Canvas(res[0],res[1]);

    Vec3 top_left_pixel = vec3_zero;

    double focus_distance;

    void update_aspect_ratio();
    void update_axes();
    void initialize_values();
    void update_size();
    Vec3 get_pixel_local_pos(const int &, const int &);
    Vec3 shoot_ray_from_pixel(const int &, const int &);
    void render();

};
