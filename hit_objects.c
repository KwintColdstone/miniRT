#include "miniRT.h"

static void set_face_normal(const t_ray *r, const t_vec3 *outward_normal, t_hit_record *rec)
{
	rec->front_face = dot_vec3(r->direction, *outward_normal) < 0;
	if (rec->front_face == true)
		rec->normal = *outward_normal;
	else
		rec->normal = multiply_by_scalar(*outward_normal, -1.0);
}

bool	sphere_hit(const t_sphere *s, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	t_vec3 oc = subtract_vec3(s->center, r->origin);
	double a = vec3_len_squared(r->direction);
	double h = dot_vec3(r->direction, oc);
	double c = vec3_len_squared(oc) - s->radius*s->radius;
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
	t_vec3 outward_normal = divide_by_scalar(subtract_vec3(rec->position, s->center), s->radius);
	set_face_normal(r, &outward_normal, rec);
	rec->mat = s->mat;
	return (true);
}

bool	plane_hit(const t_plane *p, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	t_vec3 n = cross_vec3(p->u, p->v);
	t_vec3 normal = unit_vector(n);
	double D = dot_vec3(normal, p->corner);
	t_vec3 w = divide_by_scalar(n, dot_vec3(n,n));

	double denom = dot_vec3(normal, r->direction);
	// No hit if the ray is parallel to the plane.
	if (fabs(denom) < 1e-8)
		return false;

	// Return false if the hit point parameter t is outside the ray interval.
	double t = (D - dot_vec3(normal, r->origin)) / denom;
	if (!interval_contains(ray_t, t))
		return (false);

	// Determine if the hit point lies within the planar shape using its plane coordinates.
	t_vec3 intersection = ray_at(r, t);
	t_vec3 planar_hitpt_vector = subtract_vec3(intersection, p->corner);
	double alpha = dot_vec3(w, cross_vec3(planar_hitpt_vector, p->v));
	double beta = dot_vec3(w, cross_vec3(p->u, planar_hitpt_vector));

	// Check if point is within the quad bounds (0 to 1 in both directions)
	t_interval unit_interval = (t_interval){0, 1};
	if (!interval_contains(unit_interval, alpha) || !interval_contains(unit_interval, beta))
		return false;
	// Ray hits the 2D shape; set the rest of the hit record and return true.
	rec->t = t;
	rec->position = intersection;
	rec->mat = p->mat;
	set_face_normal(r, &normal, rec);
	return  (true);
}

bool	cylinder_hit(const t_cylinder *cl, const t_ray *r, t_interval ray_t, t_hit_record *rec)
{
	double a = (r->direction.x * r->direction.x) + (r->direction.z * r->direction.z);
	double b = 2 * (r->direction.x * (r->origin.x - cl->center.x) + 
				   r->direction.z * (r->origin.z - cl->center.z));
	double c = (r->origin.x - cl->center.x) * (r->origin.x - cl->center.x) + 
			   (r->origin.z - cl->center.z) * (r->origin.z - cl->center.z) - 
			   (cl->radius * cl->radius);

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	double sqrtd = sqrt(discriminant);
	double root = (-b - sqrtd) / (2 * a);
	if (root <= ray_t.min || ray_t.max <= root)
	{
		root = (-b + sqrtd) / (2 * a);
		if (root <= ray_t.min || ray_t.max <= root)
			return (false);
	}
	double hit_y = r->origin.y + root * r->direction.y;
	if (hit_y < cl->center.y || hit_y > cl->center.y + cl->height)
		return (false);
	rec->t = root;
	rec->position = ray_at(r, rec->t);
	t_vec3 outward_normal = (t_vec3){
		rec->position.x - cl->center.x,
		0.0,
		rec->position.z - cl->center.z
	};
	outward_normal = unit_vector(outward_normal);
	set_face_normal(r, &outward_normal, rec);
	rec->mat = cl->mat;
	return (true);
}
