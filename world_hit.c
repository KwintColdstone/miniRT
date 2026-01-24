#include "miniRT.h"


bool world_hit(const t_world* world, const t_ray* r,
	t_interval ray_t, t_hit_record* rec)
{
	t_hit_record	temp_rec;
	t_interval	new_ray_t;
	t_sphere	s;
	t_plane	p;
	bool hit_anything = false;
	double closest_so_far = ray_t.max;
	new_ray_t.max = ray_t.max;
	new_ray_t.min = ray_t.min;

	for (int i = 0; i < world->spheres.count; i++) {
		s.center = world->spheres.centers[i];
		s.radius = world->spheres.radii[i];
		s.mat = world->spheres.materials[i];
		if (sphere_hit(&s, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	for (int i = 0; i < world->planes.count; i++) {
		p.corner = world->planes.corners[i];
		p.u = world->planes.u[i];
		p.v = world->planes.v[i];
		p.mat = world->planes.materials[i];
		if (plane_hit(&p, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	return (hit_anything);
}
