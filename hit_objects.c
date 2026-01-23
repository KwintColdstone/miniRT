#include "miniRT.h"

void set_face_normal(const t_ray *r, const t_vec3 *outward_normal, t_hit_record *rec)
{
	rec->front_face = dot_vec3(r->direction, *outward_normal) < 0;
	if (rec->front_face == true)
		rec->normal = *outward_normal;
	else
		rec->normal = multiply_by_scalar(*outward_normal, -1.0);
}

bool	sphere_hit(const t_vec3 *center, double radius, t_material material, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	t_vec3 oc = subtract_vec3(*center, r->origin);
	double a = vec3_len_squared(r->direction);
	double h = dot_vec3(r->direction, oc);
	double c = vec3_len_squared(oc) - radius*radius;
	double discriminant = h*h - a*c;
	if (discriminant < 0)
	{
		return (false);
	}
	double sqrtd = sqrt(discriminant);
	// Find nearest root in acceptable range
	double root = (h - sqrtd) / a;
	if (root <= ray_t.min || ray_t.max <= root)
	{
		root = (h + sqrtd) / a;
		if (root <= ray_t.min || ray_t.max <= root)
			return (false);
	}
	rec->t = root;
	rec->position = ray_at(r, rec->t);
	t_vec3 outward_normal = divide_by_scalar(subtract_vec3(rec->position, *center), radius);
	set_face_normal(r, &outward_normal, rec);
	rec->mat = material;
	return (true);
}

bool	plane_hit(const t_vec3 *q, const t_vec3 *u, const t_vec3 *v, t_material material, const t_ray *r, t_interval ray_t, t_hit_record *rec) 
{
	
	return (false);
}
