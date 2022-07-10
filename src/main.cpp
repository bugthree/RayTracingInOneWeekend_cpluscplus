#include "rtweekend.h"

#include "color.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

#include <iostream>


//！ 光线颜色
//!  world 为一个hittable
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;// 与球体击中记录
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
	// 如果没有交点，那就代表光线不在球内，
    // 则按照原来的方法得到不在求内像素点的rgb
    vec3 unit_direction = unit_vector(r.direction());// 光线方向缩放到[-1 1]之间
    auto t = 0.5 * (unit_direction.y() + 1.0);// y坐标高度(屏幕的竖直方向)将用白 蓝 白蓝融合代替
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    //const int image_width = 256;
    //const int image_height = 256;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    // 定义一个击中表world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));// 增加一个球心[0 0 -1],半径0.5 球体
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));// 增加一个球心[0 -100.5 -1],半径100 球体

    // Camera
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

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            // 定义一个光线
            // lower_left_corner + u * horizontal + v * vertical 代表从屏幕左侧最低点+ 增量
            // 减去 起点 即为方向
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);// 起点+方向
            color pixel_color = ray_color(r,world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}