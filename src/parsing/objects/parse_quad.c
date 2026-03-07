/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_quad.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:49:16 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 16:28:08 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "miniRT.h"

static bool	parse_corner(t_quad *const qu, char *line, int *i)
{
	char	*corner;

	corner = extract_element(line, i, ' ');
	if (!corner)
		return (false);
	if (!assign_vec3(&qu->corner, corner, -DBL_MAX, DBL_MAX))
	{
		free(corner);
		return (false);
	}
	free(corner);
	return (true);
}

static bool	parse_u(t_quad *const qu, char *line, int *i)
{
	char	*u;

	u = extract_element(line, i, ' ');
	if (!u)
		return (false);
	if (!assign_vec3(&qu->u, u, -DBL_MAX, DBL_MAX))
	{
		free(u);
		return (false);
	}
	free(u);
	return (true);
}

static bool	parse_v(t_quad *const qu, char *line, int *i)
{
	char	*v;

	v = extract_element(line, i, ' ');
	if (!v)
		return (false);
	if (!assign_vec3(&qu->v, v, -DBL_MAX, DBL_MAX))
	{
		free(v);
		return (false);
	}
	free(v);
	return (true);
}

bool	parse_quad(t_world *world, char *line, int index)
{
	t_quad *const	qu = &world->qu_list.quads[index];
	int				i;

	i = 0;
	if (!parse_corner(qu, line, &i))
		return (minirt_perror("Failed to parse corner of quad"), false);
	if (!parse_u(qu, line, &i))
		return (minirt_perror("Failed to parse u of quad"), false);
	if (!parse_v(qu, line, &i))
		return (minirt_perror("Failed to parse v of quad"), false);
	if (!assign_material(&qu->mat, line, &i))
		return (minirt_perror("Failed to assign material of quad"), false);
	return (true);
}
