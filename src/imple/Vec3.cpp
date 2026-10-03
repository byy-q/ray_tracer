#include "../include/Vec3.hpp"

Vec3& Vec3::operator+=(const Vec3& v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const Vec3& v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

Vec3& Vec3::operator/=(const Vec3& v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const float& t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}
Vec3& Vec3::operator/=(const float& t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

float dot(const Vec3& v1,const Vec3& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
Vec3 cross_product(const Vec3& v1,const Vec3& v2)
{
    return Vec3(
        (v1[1] * v2[2] - v1[2]*v2[1]),
        (v1[2] * v2[0] - v1[0] * v2[2]),
        (v1[0] * v2[1] - v1[1] * v2[0])
    );
}

Vec3 make_unit_vector(const Vec3& v)
{
    Vec3 result = v;
    result/=result.length();
    return result;
}

Vec3 Vec3::operator*(const float& t)const
{
    return Vec3(e[0]*t,e[1]*t,e[2]*t);
}
Vec3 Vec3::operator/(const float& t)const
{
    return Vec3(e[0]/t,e[1]/t,e[2]/t);
}

Vec3 Vec3::operator+(const Vec3& v2)const
{
    return Vec3(e[0]+v2.e[0],e[1]+v2.e[1],e[2]+v2.e[2]);
}
Vec3 Vec3::operator-(const Vec3& v2)const
{
    return Vec3(e[0]-v2.e[0],e[1]-v2.e[1],e[2]-v2.e[2]);
}