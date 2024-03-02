#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto half_b = dot(oc, r.direction());
	auto c = dot(oc, oc) - radius*radius;
	auto discriminant = half_b*half_b - 4*a*c;

	if (discriminant < 0)
		return -1.0;
	else
		return (-half_b - sqrt(discriminant)) / a;

}


color rayColor(const ray& r)
{
	auto t = hit_sphere(point3(0,0, -1), 0.5, r);
	if (t > 0.0){
		vec3 normal = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5*color(normal.x()+1, normal.y()+1, normal.z()+1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5* (unit_direction.y() + 1.0);
	return (1.0-a)*color(1.0, 1.0, 1.0) + a * color (0.5, 0.7, 1.0);
}


int main() {

    // Image

		double aspect_ratio = 16.0 / 9.0;
    size_t image_width = 400;
		size_t image_height = static_cast<size_t>(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		// Camera

		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
		auto camera_center = point3(0, 0, 0);

		// calculating the vectors across the horizontal and down the vertical viewport edges
		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		// calculating the horizontal and vertical delta vectors from pixel to pixel
		auto pixel_delta_u = viewport_u / image_width;
		auto pixel_delta_v = viewport_v / image_height;

		// calculating the location of the uppor left pixel
		auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2- viewport_v/2;
		auto pixel00_loc = viewport_upper_left + 0.5* (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; ++i) {
				auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				auto ray_direction = pixel_center - camera_center;
				ray r(camera_center, ray_direction);

				color pixel_color = rayColor(r);
				writeColor(std::cout, pixel_color);
			}
    }

    std::clog << "\rDone.                 \n";
		return 0;
}
