/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:53:48 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 13:53:49 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ray_at(const t_ray *ray, double t)
{
	t_vec3	dir;

	dir = multiply_by_scalar(ray->direction, t);
	return (add_vec3(ray->origin, dir));
}
