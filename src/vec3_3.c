/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:22:11 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 14:23:21 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	vec3_len_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_len_squared(v)));
}

t_vec3	random_vec3(void)
{
	t_vec3	random;

	random = (t_vec3){random_double(), random_double(), random_double()};
	return (random);
}

t_vec3	random_vec3_mm(double min, double max)
{
	t_vec3	random;

	random = (t_vec3){random_double_mm(min, max),
		random_double_mm(min, max), random_double_mm(min, max)};
	return (random);
}
