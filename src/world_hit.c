#include "miniRT.h"

bool world_hit(const t_world* world, const t_ray* r,
	t_interval ray_t, t_hit_record* rec)
{
	t_hit_record	temp_rec;
	t_interval	new_ray_t;
	t_sphere	sp;
	t_quad		qu;
	t_cylinder	cy;
	t_plane		pl;
	bool hit_anything = false;
	double closest_so_far = ray_t.max;
	new_ray_t.max = ray_t.max;
	new_ray_t.min = ray_t.min;

	for (int i = 0; i < world->sp_list.count; i++) {
		sp.center = world->sp_list.spheres[i].center;
		sp.radius = world->sp_list.spheres[i].radius;
		sp.mat = world->sp_list.spheres[i].mat;
		if (sphere_hit(&sp, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	for (int i = 0; i < world->qu_list.count; i++) {
		qu.corner = world->qu_list.quads[i].corner;
		qu.u = world->qu_list.quads[i].u;
		qu.v = world->qu_list.quads[i].v;
		qu.mat = world->qu_list.quads[i].mat;
		if (quad_hit(&qu, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	for (int i = 0; i < world->cy_list.count; i++) {
		cy.center = world->cy_list.cylinders[i].center;
		cy.axis = world->cy_list.cylinders[i].axis;
		cy.radius = world->cy_list.cylinders[i].radius;
		cy.height = world->cy_list.cylinders[i].height;
		cy.mat = world->cy_list.cylinders[i].mat;
		if (cylinder_hit(&cy, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	for (int i = 0; i < world->pl_list.count; i++) {
		pl.point = world->pl_list.planes[i].point;
		pl.normal = world->pl_list.planes[i].normal;
		pl.mat = world->pl_list.planes[i].mat;
		if (plane_hit(&pl, r, new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t.max = closest_so_far;
			*rec = temp_rec;
		}
	}
	return (hit_anything);
}
