#include "../include/sphere.hpp"
#include "../include/Ray.hpp"
#include "../include/Vec3.hpp"
#include "../include/hitable.hpp"
#include <cmath>

bool sphere::hit(const Ray& r, const float& t_min, const float& t_max, hit_record& record) const
{
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(),r.direction());
    float b = dot(oc,r.direction());
    float c = dot(oc,oc) - radius * radius;
    float discriminant = b*b - a*c; 
    
    if(discriminant > 0)
    {
        float temp = (-b -std::sqrt(b*b -a*c) ) / a;
        if(temp > t_min && temp < t_max)
        {
            //doing record
            record.t = temp;
            record.p = r.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;//unit vector
            record.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + std::sqrt(b*b - a*c) ) / a;
        if(temp > t_min && temp < t_max)
        {
            record.t = temp;
            record.p = r.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}