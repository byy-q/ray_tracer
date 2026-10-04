#ifndef Vec3_H__
#define Vec3_H__
//this 3 dimensional vector can be used for coordinate or RGB

#include <math.h>

class Vec3
{

    public:
        Vec3(){}
        Vec3(float e1,float e2,float e3){e[0] = e1,e[1] = e2,e[2] = e3;}
        ~Vec3(){}
        inline float x()const{return e[0];}
        inline float y()const{return e[1];}
        inline float z()const{return e[2];}
        inline float r()const{return e[0];}
        inline float g()const{return e[1];}
        inline float b()const{return e[2];}

        inline const Vec3& operator+()const{return *this;}
        inline Vec3 operator-() const{return Vec3(-e[0],-e[1],-e[2]);}
        inline float operator[](int i)const{return e[i];}
        inline float& operator[](int i){return e[i];}

        Vec3& operator+=(const Vec3& v2);
        Vec3& operator-=(const Vec3& v2);
        Vec3& operator*=(const Vec3& v2);//this is for color,not for location
        Vec3 operator*(const Vec3& v2){Vec3 result = *this;result*=v2;return result;}
        Vec3& operator/=(const Vec3& v2);//same as up
        Vec3 operator/(const Vec3& v2){Vec3 result = *this;result/=v2;return result;}
        Vec3& operator*=(const float& t);
        Vec3& operator/=(const float& t);
        Vec3 operator*(const float& t)const;
        Vec3 operator/(const float& t)const;
        Vec3 operator+(const Vec3& v2)const;
        Vec3 operator-(const Vec3& v2)const;


        friend float dot(const Vec3& v1,const Vec3& v2);
        friend Vec3 cross_product(const Vec3& v1,const Vec3& v2);

        inline float length(){return sqrt(e[0]*e[0] + e[1] * e[1] + e[2] * e[2]);}
        inline float squared_length(){return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];}
        friend Vec3 make_unit_vector(const Vec3& v);

    private:

        float e[3];
};










#endif
