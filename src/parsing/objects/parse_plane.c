/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_plane.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:34:25 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "miniRT.h"

static bool	parse_point(char *line, t_plane *const pl, int *i)
{
	char	*point;

	point = extract_element(line, i, ' ');
	if (!point)
		return (false);
	if (!assign_vec3(&pl->point, point, -DBL_MAX, DBL_MAX))
	{
		free(point);
		return (false);
	}
	free(point);
	return (true);
}

static bool	parse_normal(char *line, t_plane *const pl, int *i)
{
	char	*normal;

	normal = extract_element(line, i, ' ');
	if (!normal)
		return (false);
	if (!assign_vec3(&pl->normal, normal, -1.0, 1.0))
	{
		free(normal);
		return (false);
	}
	free(normal);
	pl->normal = unit_vector(pl->normal);
	return (true);
}

bool	parse_plane(t_world *world, char *line, int index)
{
	t_plane *const	pl = &world->pl_list.planes[index];
	int				i;

	i = 0;
	if (!parse_point(line, pl, &i))
		return (minirt_perror("Failed to parse plane point"), false);
	if (!parse_normal(line, pl, &i))
		return (minirt_perror("Failed to parse plane normal"), false);
	if (!assign_material(&pl->mat, line, &i))
		return (minirt_perror("Failed to assign plane material"), false);
	return (true);
}
