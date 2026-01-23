#include "miniRT.h"

bool world_hit(const t_world* world, const t_ray* r,
	t_interval ray_t, t_hit_record* rec)
{
	t_hit_record temp_rec;
	t_interval new_ray_t;
	bool hit_anything = false;
	double closest_so_far = ray_t.max;
	new_ray_t.max = ray_t.max;
	new_ray_t.min = ray_t.min;

	// Check all spheres
	for (int i = 0; i < world->spheres.count; i++) {
		if (sphere_hit(&world->spheres.centers[i], world->spheres.radii[i], world->spheres.materials[i], r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
			//rec->mat_index = world->spheres.mat_indices[i]; // Material reference
		}
	}
	return (hit_anything);
}
