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
        Camera(const float& vfov,const float& aspect);
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

Camera :: Camera(const float& vfov,const float& aspect)
{
    float pi = std::numbers::pi;
    float theta = vfov * pi/180;
    float half_height = tan(theta);
    float half_width = aspect * half_height;
    
    origin = Vec3(0.0,0.0,0.0);
    lower_left_corner = Vec3(-half_width,-half_height,-1.0);
    horizontal = Vec3(2*half_width,0.0,0.0); 
    vertical = Vec3(0.0,2*half_height,0.0);
}




#endif