#include <iostream>
#include <fstream>
#include <limits>
#include "include/Vec3.hpp"
#include "include/Ray.hpp"
#include "include/hitable.hpp"
#include "include/sphere.hpp"
#include "include/hitable_list.hpp"

/*
观察点位于（0，0，0），屏幕位于（-2，-1，-1）到（2，1，-1），屏幕的宽度为4，高度为2
屏幕的左下角为（-2，-1，-1），右上
角为（2，1，-1），屏幕的中心为（0，0，-1）
屏幕的宽度为4，高度为2，屏幕的左下角为
（-2，-1，-1），右上角为（2，1，-1），屏幕的中心为（0，0，-1）
所有眼睛观察到的东西，根据光路可逆原理，可以看作是从我们眼睛发出的光线，光线从眼睛出发，经过屏幕，最终到达物体表面
*/

Vec3 color(const Ray& r,hitable* world)
{
    hit_record record;
    if(world->hit(r,0.0,std::numeric_limits<float>::max(),record))
    {
        return Vec3(record.normal.x() + 1,record.normal.y()+1,record.normal.z()+1)/2;
    }
    Vec3 unit_direction = make_unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return Vec3(1.0,1.0,1.0) * (1.0 - t) + Vec3(0.5,0.7,1.0) * t;
}

int main()
{
    int nx = 200;
    int ny = 100;
    std::ofstream image_file("images/P3.ppm");
    image_file<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    Vec3 lower_left_corner(-2.0,-1.0,-1.0);
    Vec3 horizontal(4.0,0.0,0.0);
    Vec3 vertical(0.0,2.0,0.0);
    Vec3 origin(0.0,0.0,0.0);
    hitable* list[2];
    list[0] = new sphere(Vec3(0,0,-1),0.5);
    list[1] = new sphere(Vec3(0,-100.5,-1),100);
    hitable* world = new hitable_list(list,2);
    for(int j = ny-1;j>=0;j--)
    {
        for(int i = 0;i < nx;i++)
        {
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            Ray r(origin, lower_left_corner + horizontal * u + vertical * v);//this is the ray from the origin to the pixel

            Vec3 col = color(r,world);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            image_file<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }

}