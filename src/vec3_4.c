/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:23:45 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 14:25:28 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_vec3	unit_vector(t_vec3 v)
{
	return (divide_by_scalar(v, vec3_length(v)));
}

t_vec3	random_unit_vector(void)
{
	t_vec3	p;
	double	lensq;

	while (true)
	{
		p = random_vec3_mm(-1, 1);
		lensq = vec3_len_squared(p);
		if (1e-160 < lensq && lensq <= 1)
			return (divide_by_scalar(p, sqrt(lensq)));
	}
}

// In the same hemisphere as the normal
t_vec3	random_on_hemisphere(const t_vec3 *normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = random_unit_vector();
	if (dot_vec3(on_unit_sphere, *normal) > 0.0)
		return (on_unit_sphere);
	else
		return (multiply_by_scalar(on_unit_sphere, -1.0));
}

t_vec3	reflect(const t_vec3 *v, const t_vec3 *n)
{
	return (subtract_vec3(*v, multiply_by_scalar(*n, 2 * dot_vec3(*v, *n))));
}

// Return true if the vector is close to zero in all dimensions.
bool	near_zero(t_vec3 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s));
}
