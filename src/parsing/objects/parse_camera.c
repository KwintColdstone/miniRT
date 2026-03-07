/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_camera.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 15:47:50 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:20:32 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "miniRT.h"

static bool	assign_pos(t_camera *cam, char **pos)
{
	if (!assign_vec3(&cam->camera_center, *pos, -DBL_MAX, DBL_MAX))
	{
		free(*pos);
		return (false);
	}
	free(*pos);
	return (true);
}

static bool	assign_orientation(t_camera *cam, char **orientation)
{
	if (!assign_vec3(&cam->orientation, *orientation, -1.0, 1.0))
	{
		free(*orientation);
		return (false);
	}
	free(*orientation);
	return (true);
}

bool	parse_camera(t_camera *cam, char *line)
{
	int		i;
	int		hfov;
	char	*pos;
	char	*orientation;
	char	*fov;

	i = 0;
	pos = extract_element(line, &i, ' ');
	if (!pos || !assign_pos(cam, &pos))
		return (minirt_perror("Failed to parse camera position"), false);
	orientation = extract_element(line, &i, ' ');
	if (!orientation || !assign_orientation(cam, &orientation))
		return (minirt_perror("Failed to parse camera orientation"), false);
	fov = extract_element(line, &i, ' ');
	if (!fov || !is_float(fov))
	{
		free(fov);
		return (minirt_perror("Failed to parse camera fov"), false);
	}
	hfov = ft_atoi(fov);
	free(fov);
	if (hfov < 0 || hfov > 180)
		return (false);
	cam->hfov = hfov;
	return (true);
}
