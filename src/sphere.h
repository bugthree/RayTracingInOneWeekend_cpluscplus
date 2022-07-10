#ifndef SPHERE_H
#define SPHERE_H

#include "hitTable.h"
#include "vec3.h"

// 定义一个球类，管理多个球体出现的例子
// 父类是hittable
class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;// 球心
    double radius;// 半径
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    // 求解一个二元1次方程
    // 判断 光线与球是否有交点
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    // 
    auto discriminant = half_b * half_b - a * c;// 解的结果
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    //  根据求得最近的解
    rec.t = root;
    rec.p = r.at(rec.t);//  根据求得最近的解，得到光线在与球体相交的点坐标p
    vec3 outward_normal = (rec.p - center) / radius;// 根据p点与球心，可以得到一个朝外的法向
    rec.set_face_normal(r, outward_normal);// 调用该函数，求的光线是在球体内还是外

    return true;
}

#endif