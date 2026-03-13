/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   assign_vec3.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 17:29:15 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 18:11:06 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"

static void	free_xyz_strings(char *r, char *g, char *b)
{
	if (r)
		free(r);
	if (g)
		free(g);
	if (b)
		free(b);
}

static bool	assign_vector_values(t_vec3 *v, double min, double max,
	char *vec3[3])
{
	double	x;
	double	y;
	double	z;

	x = ft_atof(vec3[0]);
	printf("x: %f\n", x);
	y = ft_atof(vec3[1]);
	z = ft_atof(vec3[2]);
	free_xyz_strings(vec3[0], vec3[1], vec3[2]);
	if (x < min || x > max || y < min || y > max || z < min || z > max)
		return (minirt_perror("vec3 values outside of range"), false);
	v->x = x;
	v->y = y;
	v->z = z;
	return (true);
}

bool	assign_vec3(t_vec3 *v, char *s, double min, double max)
{
	int		i;
	char	*x_str;
	char	*y_str;
	char	*z_str;

	i = 0;
	x_str = extract_element(s, &i, ',');
	if (!x_str || ft_strcmp(x_str, "") == 0)
		return (free_xyz_strings(x_str, NULL, NULL), false);
	y_str = extract_element(s, &i, ',');
	if (!y_str || ft_strcmp(y_str, "") == 0)
		return (free_xyz_strings(x_str, y_str, NULL), false);
	z_str = extract_element(s, &i, ' ');
	if (!z_str || ft_strcmp(z_str, "") == 0)
		return (free_xyz_strings(x_str, y_str, z_str), false);
	if (!is_float(x_str) || !is_float(y_str) || !is_float(z_str))
	{
		free_xyz_strings(x_str, y_str, z_str);
		return (minirt_perror("vec3 values are not floats"), false);
	}
	if (!assign_vector_values(v, min, max, (char *[3]){x_str, y_str, z_str}))
		return (false);
	return (true);
}
