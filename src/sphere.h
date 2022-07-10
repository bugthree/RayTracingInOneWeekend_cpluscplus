#ifndef SPHERE_H
#define SPHERE_H

#include "hitTable.h"
#include "vec3.h"

// ����һ�����࣬������������ֵ�����
// ������hittable
class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;// ����
    double radius;// �뾶
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    // ���һ����Ԫ1�η���
    // �ж� ���������Ƿ��н���
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    // 
    auto discriminant = half_b * half_b - a * c;// ��Ľ��
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    //  �����������Ľ�
    rec.t = root;
    rec.p = r.at(rec.t);//  �����������Ľ⣬�õ��������������ཻ�ĵ�����p
    vec3 outward_normal = (rec.p - center) / radius;// ����p�������ģ����Եõ�һ������ķ���
    rec.set_face_normal(r, outward_normal);// ���øú�������Ĺ������������ڻ�����

    return true;
}

#endif