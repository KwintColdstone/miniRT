/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:48:08 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/09 13:52:40 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//random scatter
//direction = random_on_hemisphere(&rec.normal);
// Catch degenerate scatter direction
bool	lambertian_scatter(const t_hit_record *rec,
			t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	scatter_direction;

	scatter_direction = add_vec3(rec->normal, random_unit_vector());
	if (near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = (t_ray){rec->position, scatter_direction};
	*attenuation = rec->mat.albedo;
	return (true);
}

bool	metal_scatter(const t_ray *r_in, const t_hit_record *rec,
			t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	reflected;

	reflected = reflect(&r_in->direction, &rec->normal);
	reflected = add_vec3(unit_vector(reflected),
			multiply_by_scalar(random_unit_vector(), rec->mat.fuzz));
	*scattered = (t_ray){rec->position, reflected};
	*attenuation = rec->mat.albedo;
	return (dot_vec3(scattered->direction, rec->normal) > 0);
}
