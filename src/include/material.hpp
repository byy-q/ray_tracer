#ifndef MATERIAL_H__
#define MATERIAL_H__

#include <random>

#include "hitable.hpp"
#include "hitable_list.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

Vec3 random_in_unit_sphere();
bool refract(const Vec3& v,const Vec3& n,const float& ni_over_nt,Vec3& refracted);
extern std::mt19937 rng;
extern std::uniform_real_distribution<float> random01;

class material
{
    public:
        virtual bool scatter(const Ray& r_in,const hit_record& rec,Vec3& attenuation,Ray& scattered) const = 0;
};


class lambertian:public material
{
    public:
        lambertian(const Vec3& a):albedo(a){}
        virtual bool scatter(const Ray& r_in,const hit_record& record,Vec3& attenuation,Ray& scattered) const override;
    private:
        Vec3 albedo;
};
/**
 * @brief compute the scattered ray and the attenuation of the ray
 * when it hits the lambertian material,
 
 * @param r_in in_coming ray
 * @param record the hit reord of the hit point
 * @param attuenuation the attentuation of the ray
 * @param scattered the scattered ray
 * @return true if the ray is scattered, false otherwise

*/
bool lambertian::scatter(const Ray& r_in,const hit_record& record,Vec3& attuenuation,Ray& scattered)const
{
    Vec3 target = record.p + record.normal + random_in_unit_sphere();
    scattered = Ray(record.p,target-record.p);
    attuenuation = albedo;
    return true;
}

Vec3 reflect(const Vec3& v,const Vec3& n)
{
    return v - n * dot(v,n) * 2;
}

class metal:public material
{
    public:
        metal(const Vec3& a,const float& f):albedo(a){if(f<1) fuzz = f;else fuzz =1;}
        virtual bool scatter(const Ray& r_in,const hit_record& record,Vec3& attuenation,Ray& scattered) const override;
    private:
        Vec3 albedo;
        float fuzz;
};
bool metal::scatter(const Ray& r_in,const hit_record& record,Vec3& attuenation,Ray& scattered) const 
{
    Vec3 reflected = reflect(make_unit_vector(r_in.direction()),record.normal);
    scattered = Ray(record.p,reflected + random_in_unit_sphere() * fuzz);
    attuenation = albedo;
    return (dot(scattered.direction(),record.normal) > 0);

}
float schlick(float cosine,float ref_idx);

class dielectric : public material
{
    public:
        dielectric(const float& ri) : ref_idx(ri){}
        virtual bool scatter(const Ray& r_in,const hit_record& record,Vec3& attuenation,Ray& scattered)const override;
    private:
        float ref_idx;
};
bool dielectric::scatter(const Ray& r_in,const hit_record& record,Vec3& attuenation,Ray& scattered)const
{
    Vec3 outward_normal;
    Vec3 reflectted = reflect(r_in.direction(),record.normal);
    float ni_over_nt;
    attuenation = Vec3(1.0,1.0,1.0);//glass material always absorb nothing
    Vec3 refracted;
    float reflect_prob;
    float cosine;
    if(dot(r_in.direction(),record.normal) > 0)
    {
        outward_normal = -record.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(),record.p)/r_in.direction().length();
    }
    else
    {
        outward_normal = record.normal;
        ni_over_nt = 1.0/ref_idx;
        cosine = -dot(r_in.direction(),record.p)/r_in.direction().length();
    }
    if(refract(r_in.direction(),outward_normal,ni_over_nt,refracted))
    {
        scattered = Ray(record.p,refracted);
        reflect_prob = schlick(cosine,ref_idx);
    }
    else
    {
        scattered = Ray(record.p,reflectted);
        reflect_prob = 1.0;
    }
    if(
        #ifdef POSIX
            drand48() < reflect_prob
        #endif
        #ifdef _WIN32
            random01(rng) < reflect_prob
        #endif
    ) 
    {
        scattered = Ray(record.p,reflectted);
    }
    else
    {
        scattered = Ray(record.p,refracted);
    }
    return true;
}



#endif