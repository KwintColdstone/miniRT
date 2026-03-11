/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:15:56 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 17:17:11 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

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

t_vec3	calc_world_normal(t_uvw *c,
		t_cyl_t t, t_vec3 *hit_local)
{
	t_vec3	normal_local;
	t_vec3	normal_world;

	normal_local = get_cylinder_normal_local(hit_local, t.min,
			t.side, t.bottom);
	normal_world = object_to_world_direction(&normal_local, c);
	return (normal_world);
}
