/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:07:11 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/05 21:58:44 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static bool	check_cap(const t_cylinder *cl, const t_ray *r, double cap_height,
		double *t_cap)
{
	t_vec3	hit;
	double	dx;
	double	dz;

	if (fabs(r->direction.y) < 1e-8)
		return (false);
	*t_cap = (cap_height - r->origin.y) / r->direction.y;
	if (*t_cap <= 0)
		return (false);
	hit = ray_at(r, *t_cap);
	dx = hit.x;
	dz = hit.z;
	return (dx * dx + dz * dz <= cl->radius * cl->radius);
}

// Check if intersection point is within cylinder height
static bool	is_intersection_within_height(const t_ray *r,
		const t_cylinder *cl, double root)
{
	double	y;

	y = r->origin.y + root * r->direction.y;
	if (y < 0 || y > cl->height)
		return (false);
	return (true);
}

// Check if first root is within bounds
// Check if second root is within bounds
static bool	check_cylinder_side(const t_cylinder *cl, const t_ray *r,
								t_interval ray_t, double *t_side)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	root;

	a = r->direction.x * r->direction.x + r->direction.z * r->direction.z;
	b = 2 * (r->direction.x * r->origin.x
			+ r->direction.z * r->origin.z);
	c = r->origin.x * r->origin.x
		+ r->origin.z * r->origin.z - cl->radius * cl->radius;
	if (fabs(a) < 1e-8)
		return (false);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	root = (-b - sqrt(disc)) / (2 * a);
	if (root <= ray_t.min || root >= ray_t.max)
		root = (-b + sqrt(disc)) / (2 * a);
	if (root <= ray_t.min || root >= ray_t.max)
		return (false);
	if (!is_intersection_within_height(r, cl, root))
		return (false);
	*t_side = root;
	return (true);
}

// Determine which part of the cylinder was hit
// Side hit: normal points radially outward
// Bottom cap hit: normal points down
// Top cap hit: normal points up
static t_vec3	get_cylinder_normal_local(const t_vec3 *hit_local, double hit_t,
										double t_side, double t_bottom)
{
	t_vec3	normal;

	if (fabs(hit_t - t_side) < 1e-8)
	{
		normal = (t_vec3){hit_local->x, 0, hit_local->z};
		return (unit_vector(normal));
	}
	else if (fabs(hit_t - t_bottom) < 1e-8)
	{
		return ((t_vec3){0, -1, 0});
	}
	else
	{
		return ((t_vec3){0, 1, 0});
	}
}

// Check for intersections in local space
// Check bottom cap (y = 0 in local space)
// Check top cap (y = height in local space)
// No intersection found
static bool	find_closest_intersection(const t_cylinder *cl,
		const t_ray *rotated_r, t_interval ray_t, t_cyl_t *t)
{
	if (check_cylinder_side(cl, rotated_r, ray_t, &t->side))
	{
		t->min = t->side;
	}
	if (check_cap(cl, rotated_r, 0, &t->bottom)
		&& t->bottom > ray_t.min && t->bottom < t->min)
	{
		t->min = t->bottom;
	}
	if (check_cap(cl, rotated_r, cl->height, &t->top)
		&& t->top > ray_t.min && t->top < t->min)
	{
		t->min = t->top;
	}
	if (t->min == INFINITY)
		return (false);
	return (true);
}

static t_vec3	calc_world_normal(t_uvw *c,
		t_cyl_t t, t_vec3 *hit_local)
{
	t_vec3	normal_local;
	t_vec3	normal_world;

	normal_local = get_cylinder_normal_local(hit_local, t.min,
			t.side, t.bottom);
	normal_world = object_to_world_direction(&normal_local, c);
	return (normal_world);
}

// Transform ray to cylinder's local coordinate system
// w is the cylinder's axis direction
bool	cylinder_hit(const t_cylinder *cl, const t_ray *r, t_interval ray_t,
			t_hit_record *rec)
{
	t_uvw	c;
	t_ray	rotated_r;
	t_cyl_t	t;
	t_vec3	hit_local;
	t_vec3	normal_world;

	t.side = INFINITY;
	t.bottom = INFINITY;
	t.top = INFINITY;
	t.min = INFINITY;
	create_orthonormal_basis(&cl->axis, &c);
	rotated_r.origin = world_to_object_space(&r->origin, &cl->center, &c);
	rotated_r.direction = world_to_object_direction(&r->direction, &c);
	if (!find_closest_intersection(cl, &rotated_r, ray_t, &t))
		return (false);
	hit_local = ray_at(&rotated_r, t.min);
	rec->t = t.min;
	rec->position = object_to_world_space(&hit_local, &cl->center, &c);
	rec->mat = cl->mat;
	normal_world = calc_world_normal(&c, t, &hit_local);
	set_face_normal(r, &normal_world, rec);
	return (true);
}
