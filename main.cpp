#include "camera.hpp"
#include "scene.hpp"
#include "shapes.hpp"
#include "vec3.hpp"

int main() {
    Scene scene = {
        Sphere(Vec3(0,2,0),1)
    };

    Camera cam = {Vec3{0,0,0},Vec3{0,1,0},{100,100},10,4,scene};
    cam.render();
}
