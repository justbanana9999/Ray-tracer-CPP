#pragma once

#include <array>
#include <iosfwd>
#include <random>
#include <vector>

struct Vec3 {
    double x,y,z;

    Vec3(
        double x = 0,
        double y = 0,
        double z = 0
    ):
        x(x),
        y(y),
        z(z)
    {}

    Vec3 operator + (const Vec3 &) const;
    Vec3 operator - (const Vec3 &) const;
    Vec3 operator * (const Vec3 &) const;
    Vec3 operator / (const Vec3 &) const;

    Vec3 operator * (const double &) const;
    Vec3 operator / (const double &) const;

    Vec3 operator - () const;

    Vec3 operator += (const Vec3 & other);
    Vec3 operator *= (const Vec3 & other);

    bool operator == (const Vec3 &) const;

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

std::tuple<Vec3,Vec3,Vec3> get_relative_axes(const Vec3 &);

std::ostream & operator << (std::ostream &, const Vec3 &);

double dot(const Vec3 &, const Vec3 &);
Vec3 cross(const Vec3 &, const Vec3 &);
Vec3 reflect(const Vec3 &, const Vec3 &);

Vec3 offset_local(const std::array<Vec3,3> &, const Vec3 &);

Vec3 random_point();

Vec3 scatter_towards_normal(Vec3,std::mt19937);

Vec3 interpolate(Vec3,Vec3,double);

Vec3 sum();

Vec3 vector_average(std::pmr::vector<Vec3>);
