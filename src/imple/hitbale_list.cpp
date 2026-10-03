#include "../include/sphere.hpp"
#include "../include/Ray.hpp"
#include "../include/Vec3.hpp"
#include "../include/hitable_list.hpp"
#include "../include/hitable.hpp"

bool hitable_list::hit(const Ray& r,const float& t_min,const float& t_max,hit_record& record)const
{
    hit_record temp_record;
    bool hit_anything = false;
    float closet_so_far = t_max;
    for(int i = 0;i<list_size;i++)
    {
        if(list[i]->hit(r,t_min,closet_so_far,temp_record))
        {
            hit_anything = true;
            closet_so_far = temp_record.t;//consider for the blocker object,so that we can get the nearest intersection point
            record = temp_record;
        }
    }
    return hit_anything;
}
