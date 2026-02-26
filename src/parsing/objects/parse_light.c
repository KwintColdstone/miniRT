/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_light.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:26:12 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:35:12 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

static bool	assign_pos(t_world *world, char **pos)
{
	if (!assign_vec3(&world->light.position, *pos, -DBL_MAX, DBL_MAX))
	{
		ft_putstr_fd("assigning vec3 failed: pos\n", STDERR_FILENO);
		free(*pos);
		return (false);
	}
	free(*pos);
	return (true);
}

static bool	assign_brightness(t_world *world, char **brightness)
{
	if (!assign_float(&world->light.brightness, *brightness, 0.0, 1.0))
	{
		ft_putstr_fd("assigning brightness failed: pos\n", STDERR_FILENO);
		free(*brightness);
		return (false);
	}
	free(*brightness);
	return (true);
}

static bool	local_assign_color(t_world *world, char **color)
{
	if (!assign_color(&world->light.color, *color, 1))
	{
		ft_putstr_fd("assigning color failed\n", STDERR_FILENO);
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
	if (!pos || !assign_pos(world, &pos))
		return (false);
	brightness = extract_element(line, &i, ' ');
	if (!brightness || !assign_brightness(world, &brightness))
		return (false);
	color = extract_element(line, &i, ' ');
	if (!color || !local_assign_color(world, &color))
		return (false);
	return (true);
}
