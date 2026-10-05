#ifndef CAMERA_H__
#define CAMERA_H__

#include <numbers>
#include "Vec3.hpp"
#include "Ray.hpp"
#include <math.h>
/** 
 * @brief The camera class using three coordinates to specify a creen 
 * and one coordinate to specify the inspect point of the cameral
*/
class Camera
{
    public:
        Camera(){}
        Camera(const Vec3& look_from,const Vec3& look_at,const Vec3& view_up,const float& vfov,const float& aspect);
        Ray get_ray(float u,float v)const
        {
            return Ray(origin,lower_left_corner + horizontal*u+vertical*v - origin);
        }

    private:
        Vec3 origin;//the inspect point of the camera
        Vec3 lower_left_corner;//the left down corner of the creen
        Vec3 horizontal;//the horizontal vector of the screen
        Vec3 vertical;//the vertival vector of the screen
};

Camera :: Camera(const Vec3& look_from,const Vec3& look_at,const Vec3& view_up,const float& vfov,const float& aspect)
{
    float pi = std::numbers::pi;
    float theta = vfov * pi/180;
    float half_height = tan(theta);
    float half_width = aspect * half_height;
    Vec3 u,v,w;

    w = make_unit_vector(look_from - look_at);
    u = make_unit_vector(cross_product(view_up,w));
    v = cross_product(w,u);

    origin = look_from;
    lower_left_corner = origin - u * half_width - v * half_height - w;
    horizontal = u*2*half_width;
    vertical = v*2*half_height;
}




#endif