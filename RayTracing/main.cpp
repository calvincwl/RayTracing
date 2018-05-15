#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
using namespace std;

vec3 color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	int nx = 200;
	int ny = 100;
	fstream fileOut("../bin/output.ppm", ios::out);
	fileOut << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0, 0);
	vec3 vertical(0, 2.0f, 0);
	vec3 origin(0, 0, 0);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			fileOut << ir << " " << ig << " " << ib << "\n";
		}
	}
	fileOut.flush();
	fileOut.close();
}