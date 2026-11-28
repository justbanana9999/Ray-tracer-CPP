#pragma once

#include "vec3.hpp"

struct Ray {
    Vec3 origin,dir;
    Vec3 color = vec3_one;
    Vec3 incoming = vec3_zero;
};
