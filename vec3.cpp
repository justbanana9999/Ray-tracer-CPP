#include "vec3.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <ostream>
#include <tuple>

const Vec3 vec3_zero{0,0,0};
const Vec3 vec3_one{1,1,1};
const Vec3 vec3_front{0,1,0};
const Vec3 vec3_right{1,0,0};
const Vec3 vec3_up{0,0,1};

Vec3 Vec3::operator + (const Vec3 & other) const {
    return {x+other.x,y+other.y,z+other.z};
}
Vec3 Vec3::operator - (const Vec3 & other) const {
    return {x-other.x,y-other.y,z-other.z};
}
Vec3 Vec3::operator * (const Vec3 & other) const {
    return {x*other.x,y*other.y,z*other.z};
}
Vec3 Vec3::operator / (const Vec3 & other) const {
    return {x/other.x,y/other.y,z/other.z};
}

Vec3 Vec3::operator * (const double & other) const {
    return {x*other,y*other,z*other};
}
Vec3 Vec3::operator / (const double & other) const {
    return {x/other,y/other,z/other};
}

Vec3 Vec3::operator - () const {
    return {-x,-y,-z};
}

bool Vec3::operator == (const Vec3 & other) const {
    return x == other.x && y == other.y && z == other.z;
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
    // std::cout << other-*this << "\n";
    return (other-*this).normalized();
};

std::tuple<Vec3,Vec3,Vec3> get_relative_axes(const Vec3 & n){
    Vec3 front,right,up;

    if (n.length_squared() == 0) {
        front = -vec3_up;
    } else {
        front = n;
    }

    if (front == vec3_up) {
        right = -vec3_right;
    } else if (front == -vec3_up) {
        right = vec3_right;
    } else {
        right = cross(front,vec3_up).normalized();
    }

    up = cross(right,front).normalized();

    return {front,right,up};
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

Vec3 offset_local(const std::array<Vec3,3> & orientation, const Vec3 & offset) {
    return orientation[0]*offset.x + orientation[1]*offset.y + orientation[2]*offset.z;
}
