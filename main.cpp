#include "vec3.hpp"

#include <iostream>

int main() {
    Vec3 a{1,2,3};
    Vec3 b{4,5,6};

    Vec3 sum = a+b;

    std::cout << sum << "\n";
    std::cout << Vec3{1,1,1}.normalized();
}
