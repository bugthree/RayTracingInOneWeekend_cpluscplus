#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// 击中记录
struct hit_record {
    point3 p;
    vec3 normal;// 法线
    double t;// 光线与球体相交而得到的二元一次方程解
    bool front_face;

    // 一个P点它的法向有两个，一个指向球体内，一个向外(约定)
    // 如果光线和法向在相同的方向上，则光线在物体内部，
    // 如果光线和法向在相反的方向上，则光线在物体外面
    // 通过取两个向量的点积来确定，如果它们的点积为正，则光线在球体内,否则在外
    // 计算光线与方向法向是否相同
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// 一个击中表，用来管理多个球与光线相交的情况
class hittable {
public:
    // 一个纯虚函数
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif