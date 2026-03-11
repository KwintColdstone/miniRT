/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_light.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:26:12 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:36:59 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include <stdbool.h>

static bool	parse_pos(t_world *world, char **pos)
{
	if (!assign_vec3(&world->light.position, *pos, -DBL_MAX, DBL_MAX))
	{
		free(*pos);
		return (false);
	}
	free(*pos);
	return (true);
}

static bool	parse_brightness(t_world *world, char **brightness)
{
	if (!assign_float(&world->light.brightness, *brightness, 0.0, 1.0))
	{
		free(*brightness);
		return (false);
	}
	free(*brightness);
	return (true);
}

static bool	parse_color(t_world *world, char **color)
{
	if (!assign_color(&world->light.color, *color, 1))
	{
		free(*color);
		return (false);
	}
	free(*color);
	return (true);
}

bool	parse_light(t_world *world, char *line)
{
	int		i;
	char	*pos;
	char	*brightness;
	char	*color;

	i = 0;
	pos = extract_element(line, &i, ' ');
	if (!pos || !parse_pos(world, &pos))
		return (minirt_perror("Failed to parse light position"), false);
	brightness = extract_element(line, &i, ' ');
	if (!brightness || !parse_brightness(world, &brightness))
		return (minirt_perror("Failed to parse light brightness"), false);
	color = extract_element(line, &i, ' ');
	if (!color || !parse_color(world, &color))
		return (minirt_perror("Failed to parse light color"), false);
	return (true);
}
