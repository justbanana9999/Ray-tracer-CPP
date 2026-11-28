#pragma once

#include "material.hpp"
#include "vec3.hpp"
#include <string>
#include <vector>

struct Sphere{
    Vec3 center;
    double radius;
    Material material;
    double radius2;

    Sphere(
        Vec3 center,
        double radius,
        Material material = Material()
    ):
        center(center),
        radius(radius),
        material(material),
        radius2(radius*radius)
    {}
};

struct Triangle{
    Vec3 a,b,c;
    Material material;
    Vec3 e1,e2;
    Vec3 normal;

    Triangle(
        Vec3 a,
        Vec3 b,
        Vec3 c,
        Material material = Material()
    ):
        a(a),
        b(b),
        c(c),
        material(material),
        e1(b-a),
        e2(b-a),
        normal(cross(e1,e2).normalized())
    {}

    void generate_normal() {
        e1 = b-a;
        e2 = c-a;

        normal = cross(e1,e2).normalized();
    }

    static std::vector<Triangle> generate_plane(
        Vec3 center,
        std::pair<double,double> size,
        Material material = Material(),
        std::string orientation = "UP"

    ) {
        if (orientation == "UP") {
            return {
                Triangle(
                    Vec3(center.x+size.first,center.y-size.second,center.z),
                    Vec3(center.x-size.first,center.y+size.second,center.z),
                    Vec3(center.x-size.first,center.y-size.second,center.z),
                    material
                ),
                Triangle(
                    Vec3(center.x-size.first,center.y+size.second,center.z),
                    Vec3(center.x+size.first,center.y-size.second,center.z),
                    Vec3(center.x+size.first,center.y+size.second,center.z),
                    material
                )
            };
        } else if (orientation == "DOWN") {
            return {
                Triangle(
                    Vec3(center.x-size.first,center.y-size.second,center.z),
                    Vec3(center.x-size.first,center.y+size.second,center.z),
                    Vec3(center.x+size.first,center.y-size.second,center.z),
                    material
                ),
                Triangle(
                    Vec3(center.x+size.first,center.y+size.second,center.z),
                    Vec3(center.x+size.first,center.y-size.second,center.z),
                    Vec3(center.x-size.first,center.y+size.second,center.z),
                    material
                )
            };
        } else if (orientation == "RIGHT") {
            return {
                Triangle(
                    Vec3(center.x,center.y-size.second,center.z-size.first),
                    Vec3(center.x,center.y+size.second,center.z-size.first),
                    Vec3(center.x,center.y-size.second,center.z+size.first),
                    material
                ),
                Triangle(
                    Vec3(center.x,center.y+size.second,center.z+size.first),
                    Vec3(center.x,center.y-size.second,center.z+size.first),
                    Vec3(center.x,center.y+size.second,center.z-size.first),
                    material
                )
            };
        } else if (orientation == "LEFT") {
            return {
                Triangle(
                    Vec3(center.x,center.y-size.second,center.z+size.first),
                    Vec3(center.x,center.y+size.second,center.z-size.first),
                    Vec3(center.x,center.y-size.second,center.z-size.first),
                    material
                ),
                Triangle(
                    Vec3(center.x,center.y+size.second,center.z-size.first),
                    Vec3(center.x,center.y-size.second,center.z+size.first),
                    Vec3(center.x,center.y+size.second,center.z+size.first),
                    material
                )
            };
        } else if (orientation == "BACK") {
            return {
                Triangle(
                    Vec3(center.x-size.second,center.y,center.z-size.first),
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    material
                ),
                Triangle(
                    Vec3(center.x+size.second,center.y,center.z+size.first),
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    material
                )
            };
        } else if (orientation == "FRONT") {
            return {
                Triangle(
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    Vec3(center.x-size.second,center.y,center.z-size.first),
                    material
                ),
                Triangle(
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    Vec3(center.x+size.second,center.y,center.z+size.first),
                    material
                )
            };
        } else {
            return {
                Triangle(
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    Vec3(center.x-size.second,center.y,center.z-size.first),
                    material
                ),
                Triangle(
                    Vec3(center.x+size.second,center.y,center.z-size.first),
                    Vec3(center.x-size.second,center.y,center.z+size.first),
                    Vec3(center.x+size.second,center.y,center.z+size.first),
                    material
                )
            };
        }
    }
};
