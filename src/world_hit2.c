/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_hit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:23:50 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 17:24:07 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	is_plane_hit(const t_world *world, const t_ray *r,
	t_interval new_ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_plane			pl;
	double			closest_so_far;
	int				i;
	bool			hit_anything;

	i = 0;
	hit_anything = false;
	closest_so_far = new_ray_t.max;
	while (i < world->pl_list.count)
	{
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
		i++;
	}
	return (hit_anything);
}
