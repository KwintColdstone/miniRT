/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:59:38 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/05 16:01:36 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

// Find an arbitrary vector perpendicular to w
void	create_orthonormal_basis(const t_vec3 *axis, t_uvw *c)
{
	t_vec3	temp;

	c->w = unit_vector(*axis);
	if (fabs(c->w.x) > 0.9)
		temp = (t_vec3){0, 1, 0};
	else
		temp = (t_vec3){1, 0, 0};
	c->u = subtract_vec3(temp, multiply_by_scalar(c->w, dot_vec3(c->w, temp)));
	c->u = unit_vector(c->u);
	c->v = cross_vec3(c->w, c->u);
}

t_vec3	world_to_object_space(const t_vec3 *point,
		const t_vec3 *center, t_uvw *c)
{
	t_vec3	translated;

	translated = subtract_vec3(*point, *center);
	return ((t_vec3){
		dot_vec3(translated, c->u),
		dot_vec3(translated, c->v),
		dot_vec3(translated, c->w)
	});
}

t_vec3	object_to_world_space(const t_vec3 *point_obj,
		const t_vec3 *center, t_uvw *c)
{
	t_vec3	world_point;

	world_point = add_vec3(
			multiply_by_scalar(c->u, point_obj->x),
			multiply_by_scalar(c->v, point_obj->y)
			);
	world_point = add_vec3(world_point, multiply_by_scalar(c->w, point_obj->z));
	world_point = add_vec3(world_point, *center);
	return (world_point);
}

t_vec3	world_to_object_direction(const t_vec3 *dir, t_uvw *c)
{
	return ((t_vec3){
		dot_vec3(*dir, c->u),
		dot_vec3(*dir, c->v),
		dot_vec3(*dir, c->w)
	});
}

t_vec3	object_to_world_direction(const t_vec3 *dir_obj, t_uvw *c)
{
	t_vec3	world_dir;

	world_dir = add_vec3(
			multiply_by_scalar(c->u, dir_obj->x),
			multiply_by_scalar(c->v, dir_obj->y)
			);
	world_dir = add_vec3(world_dir, multiply_by_scalar(c->w, dir_obj->z));
	return (world_dir);
}
