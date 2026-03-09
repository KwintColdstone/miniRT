/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:16:00 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 14:24:15 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "math.h"

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vec3	add_by_scalar(t_vec3 a, double b)
{
	t_vec3	sum;

	sum.x = a.x + b;
	sum.y = a.y + b;
	sum.z = a.z + b;
	return (sum);
}

t_vec3	subtract_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x - b.x;
	sum.y = a.y - b.y;
	sum.z = a.z - b.z;
	return (sum);
}

t_vec3	subtract_by_scalar(t_vec3 a, double b)
{
	t_vec3	sum;

	sum.x = a.x - b;
	sum.y = a.y - b;
	sum.z = a.z - b;
	return (sum);
}

double	dot_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
