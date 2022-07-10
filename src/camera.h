#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

// 定义一个管理相机的类
class camera {
    public:

        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            // 视口
            auto viewport_height = 2.0;// 高
            auto viewport_width = aspect_ratio * viewport_height;// 宽
            auto focal_length = 1.0;

            auto origin = point3(0, 0, 0);// 起点 eye位置
            // 坐标系的定义：
            // x - 沿屏幕的宽度方向,从左向右为正
            // y - 沿屏幕的高度方向，有下向上为正
            // z - 右手笛卡尔坐标系定义， 从屏幕内指向外为正
            auto horizontal = vec3(viewport_width, 0, 0);// 定义水平方向，也就是屏幕的宽度
            auto vertical = vec3(0, viewport_height, 0);// 定义垂直方向，也就是屏幕的高度
            // 窗口最左低处
            auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        point3 origin;                  // 起点
        point3 lower_left_corner;       // 屏幕最左下方的像素
        vec3 horizontal;                // 屏幕水平方向
        vec3 vertical;                  // 屏幕垂直方向
};
#endif