/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:47:27 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 17:22:16 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "math.h"

// Find nearest root in acceptable range
bool	sphere_hit(const t_sphere *s, const t_ray *r,
			t_interval ray_t, t_hit_record *rec)
{
	double	root;

	if (!calculate_sphere_root(s, r, ray_t, &root))
		return (false);
	fill_sphere_hit_record(rec, s, r, root);
	return (true);
}

// No hit if the ray is parallel to the quad
// Return false if the hit point parameter t is outside the ray interval
bool	calc_t(const t_ray *r, double *t, t_vec3 normal, double d)
{
	double	denom;

	denom = dot_vec3(normal, r->direction);
	if (fabs(denom) < 1e-8)
		return (false);
	*t = (d - dot_vec3(normal, r->origin)) / denom;
	return (true);
}

// Check if point is within the quad bounds (0 to 1 in both directions)
bool	is_hit_within_quad_bounds(const t_quad *p,
			const t_ray *r, t_vec3 w, double t)
{
	t_vec3		intersection;
	t_vec3		planar_hitpt_vector;
	double		alpha;
	double		beta;
	t_interval	unit_interval;

	intersection = ray_at(r, t);
	planar_hitpt_vector = subtract_vec3(intersection, p->corner);
	alpha = dot_vec3(w, cross_vec3(planar_hitpt_vector, p->v));
	beta = dot_vec3(w, cross_vec3(p->u, planar_hitpt_vector));
	unit_interval = (t_interval){0, 1};
	if (!interval_contains(unit_interval, alpha)
		|| !interval_contains(unit_interval, beta))
	{
		return (false);
	}
	return (true);
}

bool	quad_hit(const t_quad *p, const t_ray *r,
			t_interval ray_t, t_hit_record *rec)
{
	t_vec3	n;
	t_vec3	normal;
	double	d;
	t_vec3	w;
	double	t;

	n = cross_vec3(p->u, p->v);
	normal = unit_vector(n);
	d = dot_vec3(normal, p->corner);
	w = divide_by_scalar(n, dot_vec3(n, n));
	if (!calc_t(r, &t, normal, d))
		return (false);
	if (!interval_contains(ray_t, t))
		return (false);
	if (!is_hit_within_quad_bounds(p, r, w, t))
		return (false);
	rec->t = t;
	rec->position = ray_at(r, t);
	rec->mat = p->mat;
	set_face_normal(r, &normal, rec);
	return (true);
}

bool	plane_hit(const t_plane *p, const t_ray *r,
			t_interval ray_t, t_hit_record *rec)
{
	double	d;
	double	denom;
	double	t;
	t_vec3	intersection;

	d = dot_vec3(p->normal, p->point);
	denom = dot_vec3(p->normal, r->direction);
	if (fabs(denom) < 1e-8)
		return (false);
	t = (d - dot_vec3(p->normal, r->origin)) / denom;
	if (!interval_contains(ray_t, t))
		return (false);
	intersection = ray_at(r, t);
	rec->t = t;
	rec->position = intersection;
	rec->mat = p->mat;
	set_face_normal(r, &p->normal, rec);
	return (true);
}
