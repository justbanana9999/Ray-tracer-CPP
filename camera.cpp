#include "camera.hpp"
#include "canvas.hpp"
#include "intersections.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "shapes.hpp"
#include "vec3.hpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <random>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

void Camera::update_aspect_ratio() {
    aspect_ratio = (double)res.first/res.second;
}

void Camera::update_axes() {

    std::tie(front,right,up) = get_relative_axes(this->pos.point_at(look_at));
}

void Camera::initialize_values() {
    pixel_size = width/res.first;
    top_left_pixel = offset_local({right,up,front},{-(width-pixel_size)/2,(height-pixel_size)/2,focal_length/36});
}

void Camera::update_size() {
    update_aspect_ratio();
    width = std::min(aspect_ratio,double{1});
    height = std::min(1/aspect_ratio,double{1});
    focus_distance = (look_at-pos).length();
}

Vec3 Camera::get_pixel_local_pos(const int & x, const int & y) {
    return top_left_pixel + offset_local({right,up,vec3_zero},{pixel_size*x,-pixel_size*y,0});
}

Vec3 Camera::shoot_ray_from_pixel(const int & x, const int & y,std::mt19937 rng) {

    std::pmr::vector<Vec3> color_list = {};

    Vec3 start_pixel_pos = get_pixel_local_pos(x,y);

    // std::cout << start_pixel_pos << "\n";
    // std::cout << focal_length/36 << "\n";
    // std::cout << start_pixel_pos*focal_length/36 << "\n";

    Vec3 ray_target = pos + start_pixel_pos*(focal_length/36);

    for (int sample=0;sample<max_samples;sample++) {
        Vec3 ray_origin = pos;

        Vec3 ray_dir = ray_origin.point_at(ray_target);

        Ray pixel_ray = {ray_origin,ray_dir,};

        for (int bounce=0;bounce<max_bounces+3;bounce++) {
            if (bounce == max_bounces+2) {
                pixel_ray.color = vec3_zero;
            }
            std::tuple<Vec3,Vec3,Material> closest = {vec3_zero,vec3_zero,Material()};
            double min_dist = 1e6;
            for (const auto & shape : scene.shape_list) {
                Material material = std::visit([](const auto & s) {return s.material;},shape);

                auto [hit,hit_pos,hit_normal] = std::visit([& pixel_ray](const auto & s) {
                    using T = std::decay_t<decltype(s)>;
                    if constexpr (std::is_same_v<T,Sphere>) {
                        return ray_sphere_intersection(pixel_ray,s);
                    } else {
                        return ray_triangle_intersection(pixel_ray,s);
                    }
                },shape);

                if (hit && (hit_pos-pixel_ray.origin).length() < min_dist) {
                    min_dist = (hit_pos-pixel_ray.origin).length();
                    closest = {hit_pos,hit_normal,material};
                }
            }

            if (min_dist == 1e6) {
                if (bounce == 0) {
                    pixel_ray.color = vec3_zero;
                    // pixel_ray.color = pixel_ray.dir;
                    return pixel_ray.color;
                }
                // pixel_ray.incoming += pixel_ray.dir*pixel_ray.color;
                break;
            } else {
                auto [hit_pos,hit_normal,hit_color] = closest;

                Vec3 diffuse_vector = scatter_towards_normal(hit_normal,rng);
                Vec3 specular_vector = reflect(pixel_ray.dir,hit_normal);
                pixel_ray.dir = interpolate(specular_vector,diffuse_vector,hit_color.roughness);

                pixel_ray.incoming += hit_color.emission*pixel_ray.color;
                pixel_ray.color *= hit_color.diffuse;

                pixel_ray.origin = hit_pos;
            }
        }

        color_list.push_back(pixel_ray.incoming);
    }

    Vec3 color = vector_average(color_list);

    return color;
}

void Camera::render() {
    update_axes();
    update_size();
    initialize_values();

    std::vector<std::array<int,2>> remaining_pixels = {};

    for (int y=0;y<res.first;y++) {
        for (int x=0;x<res.second;x++) {
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
//         unsigned int seed = y*res.first+x;
//         std::mt19937 gen(seed);
//
//         Vec3 color = shoot_ray_from_pixel(x,y);
//
//         canvas.put_pixel(color,x,y);
//     }

    unsigned int seed;

    for (int y=0;y<res.second;y++) {
        for (int x=0;x<res.first;x++) {
            seed = y*res.first+x;
            std::mt19937 rng(seed);
            Vec3 color = shoot_ray_from_pixel(x,y,rng);
            canvas.put_pixel(color,x,y);
        }
    }

    std::ofstream file("result.txt");
    file << canvas;
    file.close();

    save_img(canvas, "result.ppm");
}
