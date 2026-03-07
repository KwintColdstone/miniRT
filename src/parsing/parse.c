/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/24 18:39:20 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:53:58 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <fcntl.h>
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <unistd.h>

static bool	check_file_name(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] == 't' && file[i - 2] == 'r' && file[i - 3] == '.')
		return (true);
	return (false);
}

static bool	validate_and_open_file(
	char *file,
	int *fd
)
{
	if (!file)
		return (minirt_perror("No file"), false);
	if (!check_file_name(file))
		return (minirt_perror("Incorrect file format. Use [name].rt"), false);
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (external_perror("System error when opening file"), false);
	return (true);
}

bool	parse(char *file, t_world *world, t_camera *cam)
{
	t_object_counter	counter;
	int					fd;

	fd = -1;
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!count_objects(fd, &counter))
		return (minirt_perror("Failed to count objects"), false);
	if (!world_init(world, &counter))
		return (minirt_perror("Failed to init world"), false);
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!assign_objects(fd, world, cam))
		return (minirt_perror("Failed to assign values to element"), false);
	return (true);
}
