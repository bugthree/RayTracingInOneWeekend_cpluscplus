#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// ���м�¼
struct hit_record {
    point3 p;
    vec3 normal;// ����
    double t;// �����������ཻ���õ��Ķ�Ԫһ�η��̽�
    bool front_face;

    // һ��P�����ķ�����������һ��ָ�������ڣ�һ������(Լ��)
    // ������ߺͷ�������ͬ�ķ����ϣ�������������ڲ���
    // ������ߺͷ������෴�ķ����ϣ����������������
    // ͨ��ȡ���������ĵ����ȷ����������ǵĵ��Ϊ�����������������,��������
    // ��������뷽�����Ƿ���ͬ
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// һ�����б�������������������ཻ�����
class hittable {
public:
    // һ�����麯��
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif