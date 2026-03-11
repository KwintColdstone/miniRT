/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   direct_lighting.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 17:08:51 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:30:16 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

// 1. Calculate direction and distance to light
// 2. Move the ray origin slightly in the direction of the light
// This prevents the ray from intersecting the same surface
// 3. Check for occluders between point and light (but not beyond the light)
static t_vec3	create_shadow_origin(const t_vec3 *point, t_vec3 light_dir)
{
	return (add_vec3(*point, multiply_by_scalar(light_dir, 0.001)));
}

static t_interval	create_shadow_t(double light_distance)
{
	return ((t_interval){0.001, light_distance - 0.001});
}

static t_ray	create_shadow_ray(t_vec3 light_dir, t_vec3 shadow_origin)
{
	return ((t_ray){shadow_origin, light_dir});
}

bool	is_in_shadow(const t_world *world, const t_vec3 *point,
					const t_light *light)
{
	t_ray			shadow_ray;
	t_hit_record	shadow_rec;
	t_interval		shadow_t;
	t_vec3			light_dir;
	double			light_distance;

	light_dir = subtract_vec3(light->position, *point);
	light_distance = vec3_length(light_dir);
	if (light_distance < 1e-6)
		return (false);
	light_dir = unit_vector(light_dir);
	shadow_ray = create_shadow_ray(light_dir,
			create_shadow_origin(point, light_dir));
	shadow_t = create_shadow_t(light_distance);
	return (world_hit(world, &shadow_ray, shadow_t, &shadow_rec));
}

t_vec3	direct_lighting(const t_world *world, t_hit_record *rec)
{
	t_vec3	direct;
	t_vec3	ambient;
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	diff;

	ambient = multiply_vec3(world->ambient, rec->mat.albedo);
	direct = ambient;
	if (world->light.brightness > 0.0)
	{
		if (!is_in_shadow(world, &rec->position, &world->light))
		{
			light_dir = unit_vector(subtract_vec3(world->light.position,
						rec->position));
			diff = fmax(dot_vec3(rec->normal, light_dir), 0.0);
			diffuse = multiply_by_scalar(
					multiply_vec3(world->light.color, rec->mat.albedo),
					diff * world->light.brightness);
			direct = add_vec3(direct, diffuse);
		}
	}
	return (direct);
}
