/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_cylinder.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:48:19 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

static bool	extract_pos(t_cylinder *const cyl, char *line, int *i)
{
	char	*pos;
	pos = extract_element(line, i, ' ');
	if (!assign_vec3(&cyl->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);
	return (true);
}

static bool	extract_axis(t_cylinder *const cyl, char *line, int *i)
{
	char	*axis;

	axis = extract_element(line, i, ' ');
	if (!assign_vec3(&cyl->axis, axis, -1.0, 1.0))
	{
		free(axis);
		return (false);
	}
	free(axis);
	cyl->axis = unit_vector(cyl->axis);
	return (true);
}

static bool	extract_diameter(t_cylinder *const cyl, char *line, int *i)
{
	char *diameter;

	diameter = extract_element(line, i, ' ');
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	cyl->radius = ft_atof(diameter) / 2;
	free(diameter);
	if (cyl->radius < 0
		|| cyl->radius > INT_MAX) {
		return (false);
	}
	return (true);
}

static bool	extract_height(t_cylinder *const cyl, char *line, int *i)
{
	char *height = extract_element(line, i, ' ');
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
	int 				i;

	i = 0;
	extract_pos(cyl, line, &i);
	extract_axis(cyl, line, &i);
	extract_diameter(cyl, line, &i);
	extract_height(cyl, line, &i);
	if (!assign_material(&cyl->mat, line, &i)) {
		printf("assign mat fail\n");
		return (false);
	}
	return (true);
}
