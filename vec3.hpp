#pragma once

#include <array>
#include <iosfwd>

struct Vec3 {
    double x,y,z;

    Vec3 operator + (const Vec3 &) const;
    Vec3 operator - (const Vec3 &) const;
    Vec3 operator * (const Vec3 &) const;
    Vec3 operator / (const Vec3 &) const;

    Vec3 operator * (const double &) const;
    Vec3 operator / (const double &) const;

    double length_squared() const;
    double length() const;

    Vec3 normalized() const;
    Vec3 point_at(const Vec3 &) const;
};

extern const Vec3 vec3_zero;
extern const Vec3 vec3_one;
extern const Vec3 vec3_front;
extern const Vec3 vec3_right;
extern const Vec3 vec3_up;

std::array<Vec3,3> make_vectors();

std::ostream & operator << (std::ostream & out, const Vec3 & v);

double dot(const Vec3 &, const Vec3 &);
Vec3 cross(const Vec3 &, const Vec3 &);
Vec3 reflect(const Vec3 &, const Vec3 &);
