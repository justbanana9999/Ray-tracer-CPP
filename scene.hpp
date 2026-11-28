#pragma once

#include "shapes.hpp"
#include <initializer_list>
#include <variant>
#include <vector>

struct Scene{
    std::vector<std::variant<Sphere,Triangle>> shape_list;

    Scene(
        std::vector<std::variant<Sphere,Triangle>> shape_list
    ):
        shape_list(shape_list)
    {}

    Scene(
        std::initializer_list<std::variant<Sphere,Triangle>> list
    ):
        shape_list(list)
    {}

    void add(std::variant<Sphere,Triangle> shape) {
        shape_list.push_back(std::move(shape));
    }

    auto begin() {return shape_list.begin();}
    auto end() {return shape_list.end();}
};
