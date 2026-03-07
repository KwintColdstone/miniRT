/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   init_world.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 19:07:21 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:07:32 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <unistd.h>

bool	world_init(t_world *world, t_object_counter *c)
{
	ft_memset(world, 0, sizeof(t_world));
	if (c->sphere_cap)
	{
		if (!sphere_list_init(&world->sp_list, c->sphere_cap))
			return (minirt_perror("Failed to init sphere list"), false);
	}
	if (c->quad_cap)
	{
		if (!quad_list_init(&world->qu_list, c->quad_cap))
			return (minirt_perror("Failed to init quad list"), false);
	}
	if (c->cylinder_cap)
	{
		if (!cylinder_list_init(&world->cy_list, c->cylinder_cap))
			return (minirt_perror("Failed to init cylinder list"), false);
	}
	if (c->plane_cap)
	{
		if (!plane_list_init(&world->pl_list, c->plane_cap))
			return (minirt_perror("Failed to init plane list"), false);
	}
	return (true);
}

void	world_destroy(t_world *world)
{
	if (!world)
		return ;
	sphere_list_destroy(&world->sp_list);
	quad_list_destroy(&world->qu_list);
	cylinder_list_destroy(&world->cy_list);
	plane_list_destroy(&world->pl_list);
}
