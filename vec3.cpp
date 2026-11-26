#include "vec3.hpp"

#include <cmath>
#include <ostream>

const Vec3 vec3_zero{0,0,0};
const Vec3 vec3_one{1,1,1};
const Vec3 vec3_front{0,1,0};
const Vec3 vec3_right{1,0,0};
const Vec3 vec3_up{0,0,1};

Vec3 Vec3::operator+(const Vec3 & other) const {
    return {x+other.x,y+other.y,z+other.z};
}
Vec3 Vec3::operator-(const Vec3 & other) const {
    return {x-other.x,y-other.y,z-other.z};
}
Vec3 Vec3::operator*(const Vec3 & other) const {
    return {x*other.x,y*other.y,z*other.z};
}
Vec3 Vec3::operator/(const Vec3 & other) const {
    return {x/other.x,y/other.y,z/other.z};
}

Vec3 Vec3::operator*(const double & other) const {
    return {x*other,y*other,z*other};
}
Vec3 Vec3::operator/(const double & other) const {
    return {x/other,y/other,z/other};
}

double Vec3::length_squared() const {
    return x*x + y*y + z*z;
}
double Vec3::length() const {
    return std::sqrt(length_squared());
}

Vec3 Vec3::normalized() const {
    const double len = length();
    return *this/len;
}
Vec3 Vec3::point_at(const Vec3 & other) const {
    return (other-*this).normalized();
};

std::array<Vec3,3> make_vectors() {
    return {{{1,0,0},{0,1,0},{0,0,1}}};
}

std::ostream & operator << (std::ostream & out, const Vec3 & v) {
    return out << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
}

double dot(const Vec3 & a, const Vec3 & b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vec3 cross(const Vec3 & a, const Vec3 & b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x,
    };
}
Vec3 reflect(const Vec3 & i, const Vec3 & n) {
    return i-n*2*dot(i,n);
}
