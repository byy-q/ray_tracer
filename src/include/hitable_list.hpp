#ifndef HITABLE_LIST_H__
#define HITABLE_LIST_H__

#include "hitable.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "sphere.hpp"

class hitable_list:public hitable
{
    public:
        hitable_list(){}
        hitable_list(hitable** l,int n):list(l),list_size(n){}
        ~hitable_list() = default;
        virtual bool hit(const Ray& r,const float& t_min,const float& t_max,hit_record& record)const override;
    private:
        hitable** list;//pointer to the base class,so that we can store different derived class
        int list_size;
};


#endif