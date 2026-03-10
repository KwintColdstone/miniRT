/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   ray_color.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 18:33:40 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:18:43 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "display.h"
#include "bonus.h"

//A unit vector is a vector with length/magnitude of exactly 1
//we use it in formulas where you only need the direction not how far in
//a particular direction it goes
// unit_direction.y goes from -1 to 1
// a transforms that to a range of 0 to 1
// so when a = 0 we get white and when a = 1 we get blue
static t_vec3	construct_sky_vec3(const double a)
{
	const t_vec3	white = {1.0, 1.0, 1.0};
	const t_vec3	blue = {0.5, 0.7, 1.0};
	const t_vec3	w_amount = multiply_by_scalar(white, (1.0 - a));
	const t_vec3	b_amount = multiply_by_scalar(blue, a);

	return (add_vec3(w_amount, b_amount));
}

static t_vec3	sky(const t_ray *r)
{
	const t_vec3	unit_direction = unit_vector(r->direction);
	const double	a = 0.5 * (unit_direction.y + 1.0);

	return (construct_sky_vec3(a));
}

// Start with emitted light
// Then generate direct lighting (ray tracing)
static t_vec3	get_direct_color(
	const t_ray *r,
	const t_world *world,
	t_hit_record *const rec
)
{
	t_vec3		color;
	t_interval	ray_t;
	t_vec3		direct;

	ray_t.min = 0.001;
	ray_t.max = INFINITY;
	if (!world_hit(world, r, ray_t, rec))
		return (sky(r));
	color = rec->mat.emit_color;
	direct = direct_lighting(world, rec);
	color = add_vec3(color, direct);
	return (color);
}

t_vec3	ray_color(
	const t_ray *r,
	const t_world *world,
	t_vec3 background,
	int depth
)
{
	t_hit_record	rec;
	t_vec3			color;
	t_ray			scattered;
	t_vec3			attenuation;
	t_vec3			indirect;

	if (depth <= 0)
		return ((t_vec3){0, 0, 0});
	color = get_direct_color(r, world, &rec);
	if (world->indirect_lighting == true)
	{
		if (rec.mat.type == MAT_LAMBERTIAN)
		{
			lambertian_scatter(&rec, &attenuation, &scattered);
			indirect = ray_color(&scattered, world, background, depth - 1);
			color = add_vec3(color, multiply_vec3(attenuation, indirect));
		}
		else if (rec.mat.type == MAT_METAL)
		{
			metal_scatter(r, &rec, &attenuation, &scattered);
			indirect = ray_color(&scattered, world, background, depth - 1);
			color = add_vec3(color, multiply_vec3(attenuation, indirect));
		}
	}
	return (color);
}
