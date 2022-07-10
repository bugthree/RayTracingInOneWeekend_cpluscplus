#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

// ����һ�������������
class camera {
    public:

        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            // �ӿ�
            auto viewport_height = 2.0;// ��
            auto viewport_width = aspect_ratio * viewport_height;// ��
            auto focal_length = 1.0;

            auto origin = point3(0, 0, 0);// ��� eyeλ��
            // ����ϵ�Ķ��壺
            // x - ����Ļ�Ŀ�ȷ���,��������Ϊ��
            // y - ����Ļ�ĸ߶ȷ�����������Ϊ��
            // z - ���ֵѿ�������ϵ���壬 ����Ļ��ָ����Ϊ��
            auto horizontal = vec3(viewport_width, 0, 0);// ����ˮƽ����Ҳ������Ļ�Ŀ��
            auto vertical = vec3(0, viewport_height, 0);// ���崹ֱ����Ҳ������Ļ�ĸ߶�
            // ��������ʹ�
            auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        point3 origin;                  // ���
        point3 lower_left_corner;       // ��Ļ�����·�������
        vec3 horizontal;                // ��Ļˮƽ����
        vec3 vertical;                  // ��Ļ��ֱ����
};
#endif