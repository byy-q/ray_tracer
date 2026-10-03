#ifndef CAMERA_H__
#define CAMERA_H__

#include "Vec3.hpp"
#include "Ray.hpp"

/** 
 * @brief The camera class using three coordinates to specify a creen 
 * and one coordinate to specify the inspect point of the cameral
*/
class Camera
{
    public:
        Camera(){}
        Camera(Vec3 lookPoint,Vec3 lower_left_corner,Vec3 horizontal,Vec3 vertical)
        :origin(lookPoint),lower_left_corner(lower_left_corner),horizontal(horizontal),vertical(vertical){}
        Ray get_ray(float u,float v)const
        {
            return Ray(origin,lower_left_corner + u*horizontal+v*vertical - origin);
        }

    private:
        Vec3 origin;//the inspect point of the camera
        Vec3 lower_left_corner;//the left down corner of the creen
        Vec3 horizontal;//the horizontal vector of the screen
        Vec3 vertical;//the vertival vector of the screen
};




#endif