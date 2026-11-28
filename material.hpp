#pragma once

#include "vec3.hpp"

struct Material {
    Vec3 diffuse;
    double roughness;
    Vec3 emission;

    Material(
        Vec3 diffuse = vec3_one,
        double roughness = 1,
        Vec3 emission = vec3_zero
    ):
        diffuse(diffuse),
        roughness(roughness),
        emission(emission)
    {}
};
