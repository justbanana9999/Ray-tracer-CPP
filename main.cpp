#include "camera.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "shapes.hpp"
#include "vec3.hpp"

int main() {

    auto plane = Triangle::generate_plane(Vec3(0,3,0),{5,5},Material(),"UP");
    Scene scene = {
        Sphere(Vec3(-2,3,1),1,Material(Vec3(1,0,0))),
        Sphere(Vec3(0,3,1),1,Material(Vec3(0,1,0))),
        Sphere(Vec3(2,3,1),1,Material(Vec3(0,0,1))),
        Sphere(Vec3(0,20,5),10,Material(vec3_zero,1,vec3_one)),
    };

    for (const Triangle & triangle : plane) {
        scene.add(triangle);
    }

    Camera cam = {Vec3{0,0,1},Vec3{0,1,1},{100,100},10,4,scene,100};
    cam.render();
}
