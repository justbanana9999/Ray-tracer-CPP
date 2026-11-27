#include "camera.hpp"
#include "vec3.hpp"

int main() {
    Camera cam = {Vec3{0,0,0},Vec3{0,1,0},{100,100},10};
    cam.render();
}
