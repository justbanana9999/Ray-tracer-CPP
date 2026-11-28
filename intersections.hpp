#pragma once

#include "ray.hpp"
#include "shapes.hpp"
#include "vec3.hpp"
#include <cmath>
#include <limits>
#include <tuple>

inline std::tuple<bool,Vec3,Vec3> ray_sphere_intersection(
    Ray ray,
    Sphere sphere
)
{
    std::tuple<bool,Vec3,Vec3> empty_return = {false,vec3_zero,vec3_zero};

    Vec3 c = sphere.center;
    double r2 = sphere.radius2;
    Vec3 o = ray.origin;

    Vec3 u = ray.dir.normalized();

    float nabla = dot(u,o-c)*dot(u,o-c) - (o-c).length_squared() + r2;

    if (nabla == 0) {
        float d = -dot(u,o-c);
        Vec3 hit_point = o+u*d;
        Vec3 normal = c.point_at(hit_point);
        if (d >= 0) {
            return {true,hit_point,normal};
        } else {
            return empty_return;
        }
    } else if (nabla > 0) {
        float d = -dot(u,o-c) - std::sqrt(nabla);
        // float d_furthest = -dot(u,o-c) - std::sqrt(nabla);
        Vec3 hit_point = o+u*d;
        Vec3 normal = c.point_at(hit_point);
        if (d >= 0) {
            return {true,hit_point,normal};
        } else {
            return empty_return;
        }
    } else {
        return empty_return;
    }
}

inline std::tuple<bool,Vec3,Vec3> ray_triangle_intersection(
    Ray ray,
    Triangle triangle
)
{
    float epsilon = std::numeric_limits<float>::epsilon();

    std::tuple<bool,Vec3,Vec3> empty_return = {false,vec3_zero,vec3_zero};

    Vec3 normal = triangle.normal;
    if (dot(normal,ray.dir) > 0) return empty_return;

    Vec3 ray_cross_e2 = cross(ray.dir,triangle.e2);
    float det = dot(triangle.e1,ray_cross_e2);

    if (std::abs(det) < epsilon) return empty_return;

    float inv_det = 1/det;
    Vec3 s = ray.origin-triangle.a;
    float u = inv_det*dot(s,ray_cross_e2);

    if (u < -epsilon || u-1 > epsilon) return empty_return;

    Vec3 s_cross_e1 = cross(s,triangle.e1);
    float v = inv_det*dot(ray.dir,s_cross_e1);

    if (v < -epsilon || u+v-1 > epsilon) return empty_return;

    float t = inv_det*dot(triangle.e2,s_cross_e1);

    if (t > epsilon) {
        return {true,ray.origin+ray.dir*t,normal};
    } else {
        return empty_return;
    }
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
