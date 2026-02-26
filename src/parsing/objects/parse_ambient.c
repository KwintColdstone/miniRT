/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   ambient.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 15:47:50 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 15:48:18 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

bool	parse_ambient(t_world *world, char *line)
{
	double	s;
	char	*strength;
	int		i;
	char	*color;

	i = 0;
	strength = extract_element(line, &i, ' ');
	if (!assign_float(&s, strength, 0.0, 1.0))
	{
		free(strength);
		return (false);
	}
	free(strength);
	color = extract_element(line, &i, ' ');
	if (!assign_color(&world->ambient, color, s))
	{
		ft_putstr_fd("assigning color failed\n", STDERR_FILENO);
		free(color);
		return (false);
	}
	free(color);
	return (true);
}
