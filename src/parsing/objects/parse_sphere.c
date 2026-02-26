/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_sphere.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:36:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:37:40 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

bool	parse_sphere(t_world *world, char *line, int index)
{
	t_sphere *const	sp = &world->sp_list.spheres[index];
	int 			i;
	char			*diameter;
	char 			*pos;

	i = 0;
	pos = extract_element(line, &i, ' ');
	if (!assign_vec3(&sp->center, pos, -DBL_MAX, DBL_MAX))
	{
		free(pos);
		return (false);
	}
	free(pos);
	diameter = extract_element(line, &i, ' ');
	if (!is_float(diameter))
	{
		free(diameter);
		return (false);
	}
	sp->radius = ft_atof(diameter) / 2;
	free(diameter);
	if (sp->radius < 0 || sp->radius > INT_MAX
		|| !assign_material(&sp->mat, line, &i))
		return (false);
	return (true);
}
