/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_plane.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:38:33 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "miniRT.h"

bool	parse_plane(t_world *world, char *line, int index)
{
	int 	i;
	char 	*point;
	char 	*normal;
	t_plane	*const pl = &world->pl_list.planes[index];

	i = 0;
	point = extract_element(line, &i, ' ');
	if (!assign_vec3(&pl->point, point, -DBL_MAX, DBL_MAX))
	{
		free(point);
		return (false);
	}
	free(point);
	normal = extract_element(line, &i, ' ');
	if (!assign_vec3(&pl->normal, normal, -1.0, 1.0))
	{
		free(normal);
		return (false);
	}
	free(normal);
	pl->normal = unit_vector(pl->normal);
	if (!assign_material(&pl->mat, line, &i))
		return (false);
	return (true);
}
