/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   bonus_parsing.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 20:26:57 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:41:15 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "bonus.h"

static int	parse_option(char *argument, t_world *world)
{
	if (ft_strcmp(argument, OPTION_INDIRECT_LIGHTING) == 0)
		world->indirect_lighting = true;
	else
	{
		minirt_perror("Incorrect bonus options");
		printf("\t--il to render indirect lighting\n");
		return (1);
	}
	return (0);
}

int	parse_bonus_options(int argc, char *argv[], t_world *world)
{
	int	i;

	if (argc == 2)
		return (0);
	if (argc > MAX_ARGC)
		return (minirt_perror("Too many arguments"), 1);
	i = 2;
	while (i < argc)
	{
		if (parse_option(argv[i], world) != 0)
			return (1);
		i++;
	}
	return (0);
}
