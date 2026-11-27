#include "camera.hpp"
#include "vec3.hpp"

int main() {
    Camera cam = {Vec3{0,0,0},Vec3{0,0,1},{100,100},1};
    cam.render();
}
