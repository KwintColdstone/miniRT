/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:21:05 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 14:21:53 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3	multiply_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x * b.x;
	sum.y = a.y * b.y;
	sum.z = a.z * b.z;
	return (sum);
}

t_vec3	multiply_by_scalar(t_vec3 a, double b)
{
	t_vec3	sum;

	sum.x = a.x * b;
	sum.y = a.y * b;
	sum.z = a.z * b;
	return (sum);
}

t_vec3	divide_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	sum;

	sum.x = a.x / b.x;
	sum.y = a.y / b.y;
	sum.z = a.z / b.z;
	return (sum);
}

t_vec3	divide_by_scalar(t_vec3 a, double b)
{
	t_vec3	sum;

	sum.x = a.x / b;
	sum.y = a.y / b;
	sum.z = a.z / b;
	return (sum);
}
