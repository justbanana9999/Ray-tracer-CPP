#pragma once

#include "vec3.hpp"
#include <string>
#include <vector>

struct Canvas {
    const int res_x,res_y;
    std::vector<Vec3> pixels;

    Canvas(int width,int height):
    res_x(width),res_y(height),pixels(width*height)
    {}

    Vec3 & get_pixel(int,int);
    const Vec3 & get_pixel(int,int) const;
    void put_pixel(Vec3,int,int);
};

std::ostream & operator << (std::ostream &, const Canvas &);

void save_img(const Canvas & canvas,const std::pmr::string & path);
