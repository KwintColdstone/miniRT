/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_cylinder.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:38:10 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

static bool	parse_pos(t_cylinder *const cyl, char *line, int *i)
{
	char	*pos;

	pos = extract_element(line, i, ' ');
	if (!pos)
		return (external_perror("malloc fail in extract_pos"), false);
	if (!assign_vec3(&cyl->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);
	return (true);
}

static bool	parse_axis(t_cylinder *const cyl, char *line, int *i)
{
	char	*axis;

	axis = extract_element(line, i, ' ');
	if (!axis)
		return (external_perror("malloc fail in extract_axis"), false);
	if (!assign_vec3(&cyl->axis, axis, -1.0, 1.0))
	{
		free(axis);
		return (false);
	}
	free(axis);
	cyl->axis = unit_vector(cyl->axis);
	return (true);
}

static bool	parse_diameter(t_cylinder *const cyl, char *line, int *i)
{
	char	*diameter;

	diameter = extract_element(line, i, ' ');
	if (!diameter)
		return (external_perror("malloc fail in extract_diameter"), false);
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	cyl->radius = ft_atof(diameter) / 2;
	free(diameter);
	if (cyl->radius < 0 || cyl->radius > INT_MAX)
		return (false);
	return (true);
}

static bool	parse_height(t_cylinder *const cyl, char *line, int *i)
{
	char	*height;

	height = extract_element(line, i, ' ');
	if (!height)
		return (external_perror("malloc fail in extract_height"), false);
	if (!assign_float(&cyl->height, height, 0.0, INT_MAX))
	{
		free(height);
		return (false);
	}
	free(height);
	return (true);
}

bool	parse_cylinder(t_world *world, char *line, int index)
{
	t_cylinder *const	cyl = &world->cy_list.cylinders[index];
	int					i;

	i = 0;
	if (!parse_pos(cyl, line, &i))
		return (minirt_perror("Failed to parse position of cylinder"), false);
	if (!parse_axis(cyl, line, &i))
		return (minirt_perror("Failed to parse axis of cylinder"), false);
	if (!parse_diameter(cyl, line, &i))
		return (minirt_perror("Failed to parse diameter of cylinder"), false);
	if (!parse_height(cyl, line, &i))
		return (minirt_perror("Failed to parse height of cylinder"), false);
	if (!assign_material(&cyl->mat, line, &i))
		return (minirt_perror("Failed to assign material to cylinder"), false);
	return (true);
}
