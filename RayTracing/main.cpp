#include <iostream>
#include <fstream>
#include <float.h>
#include <random>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace std;

extern float frand01();

vec3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
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
	list.push_back(new sphere(vec3(0, 0, -1.0f), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f))));
	list.push_back(new sphere(vec3(0, -100.5f, -1.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0))));
	list.push_back(new sphere(vec3(1.0f, 0, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f)));
	list.push_back(new sphere(vec3(-1.0f, 0, -1.0f), 0.5f, new metal(vec3(0.8f, 0.8f, 0.8f), 1.0f)));
	hitable* world = new hitable_list(list);
	camera cam;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + frand01()) / float(nx);
				float v = float(j + frand01()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			int ir = int(255.99f * sqrt(col.r()));
			int ig = int(255.99f * sqrt(col.g()));
			int ib = int(255.99f * sqrt(col.b()));

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