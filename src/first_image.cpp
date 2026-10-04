#include <iostream>
#include <fstream>
#include <limits>
#include "include/Vec3.hpp"
#include "include/Ray.hpp"
#include "include/hitable.hpp"
#include "include/sphere.hpp"
#include "include/hitable_list.hpp"
#include "include/camera.hpp"
#include "include/material.hpp"
#include <random>
/*
观察点位于（0，0，0），屏幕位于（-2，-1，-1）到（2，1，-1），屏幕的宽度为4，高度为2
屏幕的左下角为（-2，-1，-1），右上
角为（2，1，-1），屏幕的中心为（0，0，-1）
屏幕的宽度为4，高度为2，屏幕的左下角为
（-2，-1，-1），右上角为（2，1，-1），屏幕的中心为（0，0，-1）
所有眼睛观察到的东西，根据光路可逆原理，可以看作是从我们眼睛发出的光线，光线从眼睛出发，经过屏幕，最终到达物体表面
*/

std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> random01(0.0f, 1.0f);

Vec3 random_in_unit_sphere()
{
    #ifdef POSIX
    #include <stdlib.h>
    Vec3 p;
    do
    {
        p = Vec3(drand48(),drand48(),drand48())*2.0 - Vec3(1,1,1);
    }while(dot(p,p) >= 1.0);
    #endif

    #ifdef _WIN32
    Vec3 p;
    do{
        p = Vec3(random01(rng),random01(rng),random01(rng))*2.0 - Vec3(1,1,1);
    }while(dot(p,p) >= 1.0);
    #endif
    return p;
}


Vec3 color(const Ray& r,hitable* world,int depth)
{
    hit_record record;
    if(world->hit(r,0.0001,std::numeric_limits<float>::max(),record))
    {
        Ray scattered;
        Vec3 attenuation;
        if(depth < 50 && record.mat_ptr->scatter(r,record,attenuation,scattered))
            return attenuation * color(scattered,world,depth+1);
        return Vec3(0,0,0);
    }
    Vec3 unit_direction = make_unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return Vec3(1.0,1.0,1.0) * (1.0 - t) + Vec3(0.5,0.7,1.0) * t;
}
/**
 * @brief 根据斯涅尔定律计算光线穿过介质界面后的折射方向。
 * @param v 入射方向；函数内部会将其归一化。
 * @param n 单位法线，方向应从折射介质指向入射介质。
 * @param ni_over_nt 入射介质折射率与折射介质折射率之比。
 * @param refracted 输出参数；折射存在时写入单位折射方向。
 * @return true 表示存在折射方向；false 表示发生全反射（或处于判别式为零的临界情况）。
 *
 * 将入射方向分解为法线方向和切向分量。斯涅尔定律确定切向分量的缩放比例，
 * 而判别式用于计算法线分量：若判别式小于或等于零，就没有本函数接受的折射解。全反射
*/

bool refract(const Vec3& v,const Vec3& n,const float& ni_over_nt,Vec3& refracted)
{
    Vec3 unit_v = make_unit_vector(v);
    float dt = dot(unit_v,n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1-dt*dt);
    if(discriminant > 0)
    {
        refracted = (unit_v - n * dt) * ni_over_nt - n*sqrt(discriminant);
        return true;
    }
    return false;
}

float schlick(float cosine,float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::ofstream image_file("images/P3.ppm");
    image_file<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    
    Camera camera(Vec3(0,0,0),Vec3(-2.0,-1.0,-1.0),Vec3(4.0,0.0,0.0),Vec3(0.0,2.0,0.0));
    hitable* list[4];
    list[0] = new sphere(Vec3(0,0,-1),0.5,new lambertian(Vec3(0.8,0.3,0.3)));
    list[1] = new sphere(Vec3(0,-100.5,-1),100,new lambertian(Vec3(0.8,0.8,0.0)));
    list[2] = new sphere(Vec3(1,0,-1),0.5,new metal(Vec3(0.8,0.6,0.2),0.2));
    list[3] = new sphere(Vec3(-1,0,-1),0.5,new dielectric(1.5));
    hitable* world = new hitable_list(list,4);
    for(int j = ny-1;j>=0;j--)
    {
        for(int i = 0;i < nx;i++)
        {
            /*
            *@byy-q
            @brief for each pixel,we doing ns(100) times sampling to get the average color of the pixel
            so that we can get a better image,otherwise the image will be very noisy
            */
            Vec3 col(0,0,0);
            for(int s = 0;s < ns;s++)
            {
                #ifdef POSIX
                #include <stdlib.h>
                float u = float(i + std::drand48()/float(nx));
                float v = float(j + std::drand48())/float(ny);
                Ray r = camera.get_ray(u,v);
                col += color(r,world,0);
                #endif

                #ifdef _WIN32
                    float u = float(i + random01(rng))/float(nx);
                    float v = float(j + random01(rng))/float(ny);
                    Ray r = camera.get_ray(u,v);
                    col += color(r,world,0);
                #endif
            }

            col /= float(ns);
            col = Vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));//doing gamma correction,otherwise the image will be very dark
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            image_file<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }

}