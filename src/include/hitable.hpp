#ifndef HITABLE_H__
#define HITABLE_H__
//declare the hitable class ,which is the base class of all the objects that can be hit by a ray
#include "Ray.hpp"
#include "Vec3.hpp"

typedef struct
{
    float t;//the hit point is at r.origin() + t * r.direction()
    Vec3 p;//the hit point
    Vec3 normal;//the normal vector of the surface at the hit point
} hit_record;


class hitable
{
    public:
        virtual bool hit(const Ray& r,const float& t_min,const float& t_max,hit_record& rec)const = 0;
    private:
};







#endif
