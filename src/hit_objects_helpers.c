/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:19:48 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 17:21:28 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

// Checks if ray hit from the inside or outside
void	set_face_normal(const t_ray *r,
			const t_vec3 *outward_normal, t_hit_record *rec)
{
	rec->front_face = dot_vec3(r->direction, *outward_normal) < 0;
	if (rec->front_face == true)
		rec->normal = *outward_normal;
	else
		rec->normal = multiply_by_scalar(*outward_normal, -1.0);
}

void	fill_sphere_hit_record(t_hit_record *rec,
			const t_sphere *s, const t_ray *r, double root)
{
	t_vec3	outward_normal;

	rec->t = root;
	rec->position = ray_at(r, rec->t);
	outward_normal = divide_by_scalar(
			subtract_vec3(rec->position, s->center), s->radius);
	set_face_normal(r, &outward_normal, rec);
	rec->mat = s->mat;
}

bool	calculate_sphere_root(const t_sphere *s,
			const t_ray *r, t_interval ray_t, double *root)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;

	oc = subtract_vec3(s->center, r->origin);
	a = vec3_len_squared(r->direction);
	h = dot_vec3(r->direction, oc);
	c = vec3_len_squared(oc) - s->radius * s->radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return (false);
	}
	*root = (h - sqrt(discriminant)) / a;
	if (*root <= ray_t.min || ray_t.max <= *root)
	{
		*root = (h + sqrt(discriminant)) / a;
		if (*root <= ray_t.min || ray_t.max <= *root)
			return (false);
	}
	return (true);
}
