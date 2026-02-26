/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/24 18:39:20 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:59:47 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <fcntl.h>
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

static bool	check_material_type(t_material *mat, char *mat_str)
{
	t_material base;
	t_material metal;
	t_material emit;

	if (!mat_str || mat_str[0] == '\0')
	{
		base = (t_material){MAT_LAMBERTIAN,
			(t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = base;
		return (true);
	}
	if (ft_strcmp(mat_str, "METAL") == 0)
	{
		metal = (t_material){MAT_METAL,
			(t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = metal;
	}
	else if (ft_strcmp(mat_str, "EMIT") == 0)
	{
		emit = (t_material){MAT_EMIT, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, 0};
		*mat = emit;
	}
	else
		return (false);
	return (true);
}

bool	assign_material(t_material *mat, char *line, int *i)
{
	char 	*const color = extract_element(line, i, ' ');
	char 	*const mat_str = extract_element(line, i, ' ');
	bool	err_check;

	if (!check_material_type(mat, mat_str))
	{
		free(color);
		free(mat_str);
		return (false);
	}
	if (mat->type == MAT_EMIT)
		err_check = assign_color(&mat->emit_color, color, 1);
	else
		err_check = assign_color(&mat->albedo, color, 1);
	free(color);
	free(mat_str);
	return (err_check);
}

static bool	check_file_name(char *file)
{
	int i;

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
	{
		ft_putstr_fd("no file\n", STDERR_FILENO);
		return (false);
	}
	if (!check_file_name(file))
	{
		ft_putstr_fd("incorrect file name. Use: (name).rt\n", STDERR_FILENO);
		return (false);
	}
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		perror("Error");
		return (false);
	}
	return (true);
}

bool	parse(char *file, t_world *world, t_camera *cam)
{
	t_object_counter	counter;
	int 				fd;

	fd = -1;
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!count_objects(fd, &counter))
	{
		ft_putstr_fd("failed to count objects\n", STDERR_FILENO);
		return (false);
	}
	if (!world_init(world, &counter))
	{
		ft_putstr_fd("failed to init world\n", STDERR_FILENO);
		return (false);
	}
	if (validate_and_open_file(file, &fd) == false)
		return (false);
	if (!assign_objects(fd, world, cam))
	{
		ft_putstr_fd("failed to assign values to element\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
