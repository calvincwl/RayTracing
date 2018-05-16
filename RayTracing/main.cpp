#include <iostream>
#include <fstream>
#include <float.h>
#include <random>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"

using namespace std;

vec3 color(const ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0, FLT_MAX, rec))
	{
		return 0.5f * vec3(rec.normal.x() + 1.0f, rec.normal.y() + 1.0f, rec.normal.z() + 1.0f);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

float frand()
{
	int rand_val = rand() % 100;
	return float(rand_val) / 100.0f;
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	fstream fileOut("../bin/output.ppm", ios::out);
	fileOut << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0, 0);
	vec3 vertical(0, 2.0f, 0);
	vec3 origin(0, 0, 0);
	vector<hitable*> list;
	list.push_back(new sphere(vec3(0, 0, -1.0f), 0.5f));
	list.push_back(new sphere(vec3(0, -100.5f, -1.0f), 100.0f));
	hitable* world = new hitable_list(list);
	camera cam;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + frand()) / float(nx);
				float v = float(j + frand()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);
			int ir = int(255.99f * col.r());
			int ig = int(255.99f * col.g());
			int ib = int(255.99f * col.b());

			fileOut << ir << " " << ig << " " << ib << "\n";
		}
	}
	for each (hitable* obj in list)
	{
		delete obj;
	}
	fileOut.flush();
	fileOut.close();
}