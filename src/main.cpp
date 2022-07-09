#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

//! 光线与球体相交
//! 输入：球心坐标，半径和光线
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

//！ 光线颜色
//! 
color ray_color(const ray& r) {
    //vec3 unit_direction = unit_vector(r.direction());// 单位方向
    //auto t = 0.5 * (unit_direction.y() + 1.0);
    //return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);

    if (hit_sphere(point3(0, 0, -1), 0.5, r))// 如果像素点在球内，则像素点设置为红色
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());// 光线方向缩放到[-1 1]之间
    auto t = 0.5 * (unit_direction.y() + 1.0);// y坐标高度将用白 蓝 白蓝融合代替
    // color(1.0, 1.0, 1.0) 白色
    // color(0.5, 0.7, 1.0) 蓝色
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    //const int image_width = 256;
    //const int image_height = 256;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);// 起点 eye位置
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);// 起点+方向
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}