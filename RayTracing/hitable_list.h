#pragma once
#include <vector>
#include "hitable.h"
using namespace std;

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(vector<hitable*>& l) { list = l; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	vector<hitable*> list;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for each (hitable* obj in list)
	{
		if (obj->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
