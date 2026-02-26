/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_quad.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/26 17:49:16 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 17:55:05 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "miniRT.h"

static bool	extract_corner(t_quad *const qu, char *line, int *i)
{
	char	*corner;

	corner = extract_element(line, i, ' ');
	if (!assign_vec3(&qu->corner, corner, -DBL_MAX, DBL_MAX))
	{
		free(corner);
		return (false);
	}
	free(corner);
	return (true);
}

static bool	extract_u(t_quad *const qu, char *line, int *i)
{
	char	*u;

	u = extract_element(line, i, ' ');
	if (!assign_vec3(&qu->u, u, -DBL_MAX, DBL_MAX))
	{
		free(u);
		return (false);
	}
	free(u);
	return (true);
}

static bool	extract_v(t_quad *const qu, char *line, int *i)
{
	char	*v;

	v = extract_element(line, i, ' ');
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
	extract_corner(qu, line, &i);
	extract_u(qu, line, &i);
	extract_v(qu, line, &i);
	if (!assign_material(&qu->mat, line, &i))
		return (false);
	return (true);
}
