#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

//! 光线与球体相交
//! 输入：球心坐标，半径和光线
//! 输出 求解的方程解
double hit_sphere(const point3& center, double radius, const ray& r) {
    // 解二元方程
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {// 方程无解
        return -1.0;
    }
    else {// 只要了一个解，因为法向是 击中交点与球心交点，
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

//！ 光线颜色
//! 
color ray_color(const ray& r) {
    // 判断光线是否与球相交，若t=-1，则没击中
    // 否则，得到一个交点
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if(t > 0.0) {// 如果光线是与球相交
        // 使用t求解便得到光线在t点的坐标 - (0, 0, -1)球心坐标，便得到一个方向，取单位向量，就是法向量
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));// N 得到法向量 
        // 建立法向量 x y z 与颜色的关系
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    // 如果没有交点，那就代表光线不在球内，
    // 则按照原来的方法得到不在求内像素点的rgb
    vec3 unit_direction = unit_vector(r.direction());// 光线方向缩放到[-1 1]之间
    t = 0.5 * (unit_direction.y() + 1.0);// y坐标高度(屏幕的竖直方向)将用白 蓝 白蓝融合代替
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