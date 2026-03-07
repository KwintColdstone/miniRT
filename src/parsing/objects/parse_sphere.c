/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_sphere.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:29:15 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

static bool	parse_pos(char *line, t_sphere *const sp, int *i)
{
	char	*pos;

	pos = extract_element(line, i, ' ');
	if (!pos)
		return (false);
	if (!assign_vec3(&sp->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);
	return (true);
}

static bool	parse_diameter(char *line, t_sphere *const sp, int *i)
{
	char	*diameter;

	diameter = extract_element(line, i, ' ');
	if (!diameter)
		return (false);
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	sp->radius = ft_atof(diameter) / 2;
	free(diameter);
	return (true);
}

bool	parse_sphere(t_world *world, char *line, int index)
{
	t_sphere *const	sp = &world->sp_list.spheres[index];
	int				i;

	i = 0;
	if (!parse_pos(line, sp, &i))
		return (minirt_perror("Failed to parse position of sphere"), false);
	if (!parse_diameter(line, sp, &i))
		return (minirt_perror("Failed to parse diameter of sphere"), false);
	if (sp->radius < 0 || sp->radius > INT_MAX
		|| !assign_material(&sp->mat, line, &i))
		return (minirt_perror("Failed to assign material of sphere"), false);
	return (true);
}
