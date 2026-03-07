/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   assign_vec3.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 17:29:15 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 17:29:27 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	assign_vec3(t_vec3 *v, char *s, double min, double max)
{
	int i = 0;
	char *x_str = extract_element(s, &i, ',');
	char *y_str = extract_element(s, &i, ',');
	char *z_str = extract_element(s, &i, ' ');
	if (!is_float(x_str) || !is_float(y_str) || !is_float(z_str))
	{
		printf("vec3 float test failed\n");
		free(x_str);
		free(y_str);
		free(z_str);
		return (false);
	}
	double x;
	double y;
	double z;
	x = ft_atof(x_str);
	y = ft_atof(y_str);
	z = ft_atof(z_str);
	free(x_str);
	free(y_str);
	free(z_str);
	if (x < min || x > max || y < min || y > max || z < min || z > max)
	{
		printf("vec3 outside range\n");
		return (false);
	}
	v->x = x;
	v->y = y;
	v->z = z;
	return (true);
}
