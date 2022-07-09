#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

//! �����������ཻ
//! ���룺�������꣬�뾶�͹���
//! ��� ���ķ��̽�
double hit_sphere(const point3& center, double radius, const ray& r) {
    // ���Ԫ����
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {// �����޽�
        return -1.0;
    }
    else {// ֻҪ��һ���⣬��Ϊ������ ���н��������Ľ��㣬
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

//�� ������ɫ
//! 
color ray_color(const ray& r) {
    // �жϹ����Ƿ������ཻ����t=-1����û����
    // ���򣬵õ�һ������
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if(t > 0.0) {// ��������������ཻ
        // ʹ��t����õ�������t������� - (0, 0, -1)�������꣬��õ�һ������ȡ��λ���������Ƿ�����
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));// N �õ������� 
        // ���������� x y z ����ɫ�Ĺ�ϵ
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    // ���û�н��㣬�Ǿʹ�����߲������ڣ�
    // ����ԭ���ķ����õ������������ص��rgb
    vec3 unit_direction = unit_vector(r.direction());// ���߷������ŵ�[-1 1]֮��
    t = 0.5 * (unit_direction.y() + 1.0);// y����߶�(��Ļ����ֱ����)���ð� �� �����ںϴ���
    // color(1.0, 1.0, 1.0) ��ɫ
    // color(0.5, 0.7, 1.0) ��ɫ
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

    auto origin = point3(0, 0, 0);// ��� eyeλ��
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
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);// ���+����
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}