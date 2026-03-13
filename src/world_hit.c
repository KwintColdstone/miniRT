/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:04:22 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/11 16:17:11 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static bool	is_sphere_hit(const t_world *world, const t_ray *r,
	t_interval *new_ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_sphere		sp;
	double			closest_so_far;
	int				i;
	bool			hit_anything;

	i = 0;
	hit_anything = false;
	closest_so_far = new_ray_t->max;
	while (i < world->sp_list.count)
	{
		sp.center = world->sp_list.spheres[i].center;
		sp.radius = world->sp_list.spheres[i].radius;
		sp.mat = world->sp_list.spheres[i].mat;
		if (sphere_hit(&sp, r, *new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t->max = closest_so_far;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

static bool	is_quad_hit(const t_world *world, const t_ray *r,
	t_interval *new_ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_quad			qu;
	double			closest_so_far;
	int				i;
	bool			hit_anything;

	i = 0;
	hit_anything = false;
	closest_so_far = new_ray_t->max;
	while (i < world->qu_list.count)
	{
		qu.corner = world->qu_list.quads[i].corner;
		qu.u = world->qu_list.quads[i].u;
		qu.v = world->qu_list.quads[i].v;
		qu.mat = world->qu_list.quads[i].mat;
		if (quad_hit(&qu, r, *new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t->max = closest_so_far;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

static void	init_cylinder(const t_world *world, t_cylinder *cy, int i)
{
	cy->center = world->cy_list.cylinders[i].center;
	cy->axis = world->cy_list.cylinders[i].axis;
	cy->radius = world->cy_list.cylinders[i].radius;
	cy->height = world->cy_list.cylinders[i].height;
	cy->mat = world->cy_list.cylinders[i].mat;
}

static bool	is_cylinder_hit(const t_world *world, const t_ray *r,
	t_interval *new_ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_cylinder		cy;
	double			closest_so_far;
	int				i;
	bool			hit_anything;

	i = 0;
	hit_anything = false;
	closest_so_far = new_ray_t->max;
	while (i < world->cy_list.count)
	{
		init_cylinder(world, &cy, i);
		if (cylinder_hit(&cy, r, *new_ray_t, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			new_ray_t->max = closest_so_far;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

bool	world_hit(const t_world *world, const t_ray *r,
	t_interval ray_t, t_hit_record *rec)
{
	t_interval		new_ray_t;
	bool			hit_anything;

	hit_anything = false;
	new_ray_t.max = ray_t.max;
	new_ray_t.min = ray_t.min;
	if (is_sphere_hit(world, r, &new_ray_t, rec))
	{
		hit_anything = true;
	}
	if (is_quad_hit(world, r, &new_ray_t, rec))
	{
		hit_anything = true;
	}
	if (is_cylinder_hit(world, r, &new_ray_t, rec))
	{
		hit_anything = true;
	}
	if (is_plane_hit(world, r, &new_ray_t, rec))
	{
		hit_anything = true;
	}
	return (hit_anything);
}
