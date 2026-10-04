#ifndef SPHERE_H__
#define SPHERE_H__

#include "hitable.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
class sphere:public hitable
{
    public:
        sphere(){}
        sphere(const Vec3& center,const float& radius,material* ptr):center(center),radius(radius),mat_ptr(ptr){}
        ~sphere() = default;
        virtual bool hit(const Ray& r,const float& t_min,const float& t_max,hit_record& record)const override;
    private:
        Vec3 center;
        float radius;
        material *mat_ptr;
};





#endif