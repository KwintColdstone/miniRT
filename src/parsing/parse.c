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
	if (*fd < 0)
		return (external_perror("Can't open .rt file"), false);
	return (true);
}

static bool	second_pass(char *file, t_world *world, t_camera *cam)
{
	int	fd;

	fd = -1;
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!assign_objects(fd, world, cam))
	{
		close(fd);
		return (minirt_perror("Failed to assign values to element"), false);
	}
	close(fd);
	return (true);
}

static bool	first_pass(char *file, t_world *world, t_object_counter *counter)
{
	int		fd;

	fd = -1;
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!count_objects(fd, counter))
	{
		close(fd);
		return (minirt_perror("Failed to count objects"), false);
	}
	if (!world_init(world, counter))
	{
		close(fd);
		return (minirt_perror("Failed to init world"), false);
	}
	close(fd);
	return (true);
}

//these are for testing if parsing fucks up
	//printf("World sphere count: %d\n", world->sp_list.count);
	//printf("Counter sphere count: %d\n", counter.sphere_cap);
	//printf("World plane count: %d\n", world->pl_list.count);
	//printf("Counter plane count: %d\n", counter.plane_cap);
	//printf("World cylinder count: %d\n", world->cy_list.count);
	//printf("Counter culinder count: %d\n", counter.cylinder_cap);
	//printf("World quad count: %d\n", world->qu_list.count);
	//printf("Counter quad count: %d\n", counter.quad_cap);
bool	parse(char *file, t_world *world, t_camera *cam)
{
	t_object_counter	counter;

	world->light_is_parsed = false;
	world->ambient_is_parsed = false;
	cam->camera_is_parsed = false;
	if (!first_pass(file, world, &counter))
		return (false);
	if (counter.light == 0 || counter.camera == 0 || counter.ambient == 0)
		return (minirt_perror("Camera, light or ambient not set up"), false);
	if (!second_pass(file, world, cam))
		return (false);
	if (world->sp_list.count != counter.sphere_cap
		|| world->pl_list.count != counter.plane_cap
		|| world->cy_list.count != counter.cylinder_cap
		|| world->qu_list.count != counter.quad_cap)
	{
		minirt_perror("Failed sanity check on object count (parsing mismatch)");
		return (false);
	}
	if (world->light_is_parsed == false || world->ambient_is_parsed == false
		|| cam->camera_is_parsed == false)
		return (minirt_perror("Camera, light or ambient not set up"), false);
	return (true);
}
