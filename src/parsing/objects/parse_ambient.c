/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_ambient.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 15:47:50 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:39:18 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include <stdbool.h>

bool	parse_ambient(t_world *world, char *line)
{
	double	s;
	char	*strength;
	int		i;
	char	*color;

	i = 0;
	strength = extract_element(line, &i, ' ');
	if (!strength)
		return (false);
	if (!assign_float(&s, strength, 0.0, 1.0))
	{
		free(strength);
		return (minirt_perror("Failed to parse ambient strentgh"), false);
	}
	free(strength);
	color = extract_element(line, &i, ' ');
	if (!color)
		return (false);
	if (!assign_color(&world->ambient, color, s))
	{
		free(color);
		return (minirt_perror("Failed to assign ambient color"), false);
	}
	free(color);
	return (true);
}
