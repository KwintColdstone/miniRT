/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   assign_objects.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/24 18:54:03 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/24 19:12:59 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	add_to_object_count(
	bool success,
	int *count
)
{
	if (success)
		(*count)++;
}

static bool	assign_two_letter_objects(
	t_world *world,
	char *line,
	int *i
)
{
	bool	success;

	*i += 2;
	if (line[*i - 2] == 's' && line[*i - 1] == 'p')
	{
		success = parse_sphere(world, &line[*i], world->sp_list.count);
		add_to_object_count(success, &world->sp_list.count);
	}
	else if (line[*i - 2] == 'p' && line[*i - 1] == 'l')
	{
		success = parse_plane(world, &line[*i], world->pl_list.count);
		add_to_object_count(success, &world->pl_list.count);
	}
	else if (line[*i - 2] == 'c' && line[*i - 1] == 'y')
	{
		success = parse_cylinder(world, &line[*i], world->cy_list.count);
		add_to_object_count(success, &world->cy_list.count);
	}
	else if (line[*i - 2] == 'q' && line[*i - 1] == 'u')
	{
		success = parse_quad(world, &line[*i], world->qu_list.count);
		add_to_object_count(success, &world->qu_list.count);
	}
	success = true;
	return (success);
}

static bool	assign_one_letter_objects(
	t_world *world,
	t_camera *cam,
	char *line,
	int *i
)
{
	bool	success;

	success = true;
	if (line[*i] == 'A')
	{
		(*i)++;
		success = parse_ambient(world, cam, &line[*i]);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		success = parse_camera(cam, &line[*i]);
	}
	else if (line[*i] == 'L')
	{
		(*i)++;
		success = parse_light(world, &line[*i]);
	}
	return (success);
}

static bool	check_and_assign_objects_from_line(
	t_world *world,
	t_camera *cam,
	char *line,
	int *i
)
{
	bool	success;

	success = assign_one_letter_objects(world, cam, line, i);
	if (success == true)
		success = assign_two_letter_objects(world, line, i);
	return (success);
}

bool	assign_objects(int fd, t_world *world, t_camera *cam)
{
	char 	*line;
	int 	i;
	int		line_count;

	line_count = 1;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (check_and_assign_objects_from_line(world, cam, line, &i) == false)
		{
			printf("parsing failure at line: %d\n", line_count);
			printf("incorrect values for element\n");
			close(fd);
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	close(fd);
	return (true);
}
