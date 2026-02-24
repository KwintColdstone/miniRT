/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   count_objects.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/24 17:40:02 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/24 19:15:06 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// return 0 if valid one letter object
// return 1 if not
static int	check_one_letter_object(
	t_object_counter *counts,
	char *line,
	int i
)
{
	if (!ft_isspace(line[i + 1]))
		return (1);
	if (line[i] == 'A')
		counts->ambient++;
	else if (line[i] == 'C')
		counts->camera++;
	else if (line[i] == 'L')
		counts->light++;
	else
		return (1);
	return (0);
}

// return 0 if valid two letter object
// return 1 if not
// return -1 if format is bad (not whitespace after object identifier)
static int	check_two_letter_object(
	t_object_counter *counts,
	char *line,
	int i
)
{
	if (!ft_isspace(line[i + 2]) || line[i] < 'a' || line[i] > 'z')
		return (-1);
	if (line[i] == 's' && line[i+1] == 'p')
		counts->sphere_cap++;
	else if (line[i] == 'p' && line[i+1] == 'l')
		counts->plane_cap++;
	else if (line[i] == 'c' && line[i+1] == 'y')
		counts->cylinder_cap++;
	else if (line[i] == 'q' && line[i+1] == 'u')
		counts->quad_cap++;
	else
		return (1);
	return (0);
}

static bool	check_objects_in_line(
	t_object_counter *counts,
	char *line
)
{
	int	i;
	int	object_check;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i])
	{
		object_check = check_one_letter_object(counts, line, i);
		if (object_check == 1)
			object_check = check_two_letter_object(counts, line, i);
		if (object_check == -1 || object_check == 1)
		{
			printf("parsing failed at line %d: not an element\n", i);
			return (false);
		}
		if (counts->ambient > 1 || counts->light > 1 || counts->light > 1)
		{
			ft_putstr_fd("parsing failed: more than one capitalized element", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

bool	count_objects(int fd, t_object_counter *counts)
{
	char	*line;

	ft_memset(counts, 0, sizeof(t_object_counter));
	line = get_next_line(fd);
	while (line)
	{
		if (check_objects_in_line(counts, line) == false)
		{
			close(fd);
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
