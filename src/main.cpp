#include "rtweekend.h"

#include "color.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>



//�� ������ɫ
//!  world Ϊһ��hittable
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;// ��������м�¼
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
	// ���û�н��㣬�Ǿʹ�����߲������ڣ�
    // ����ԭ���ķ����õ������������ص��rgb
    vec3 unit_direction = unit_vector(r.direction());// ���߷������ŵ�[-1 1]֮��
    auto t = 0.5 * (unit_direction.y() + 1.0);// y����߶�(��Ļ����ֱ����)���ð� �� �����ںϴ���
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    //const int image_width = 256;
    //const int image_height = 256;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const int samples_per_pixel = 100;

    // World
    // ����һ�����б�world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));// ����һ������[0 0 -1],�뾶0.5 ����
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));// ����һ������[0 -100.5 -1],�뾶100 ����

    // Camera
    //     // Camera
    camera cam;
    

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                // ����һ������
                // lower_left_corner + u * horizontal + v * vertical �������Ļ�����͵�+ ����
                // ��ȥ ��� ��Ϊ����
                ray r = cam.get_ray(u, v);// ���+����
                color pixel_color = ray_color(r, world);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }

    }

    std::cerr << "\nDone.\n";
}