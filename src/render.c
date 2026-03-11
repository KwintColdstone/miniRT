/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   render.c                                                :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 19:48:41 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:18:17 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "bonus.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

static void	write_color(t_world *world, t_vec3 *pixel_color, int ppm_file)
{
	const t_interval	intensity = (t_interval){0.000, 0.999};
	double				r;
	double				g;
	double				b;

	r = linear_to_gamma(pixel_color->x);
	g = linear_to_gamma(pixel_color->y);
	b = linear_to_gamma(pixel_color->z);
	pixel_color->x = (int)(256 * clamp_interval(r, intensity));
	pixel_color->y = (int)(256 * clamp_interval(g, intensity));
	pixel_color->z = (int)(256 * clamp_interval(b, intensity));
	if (world->write_to_file == true)
		write_to_file(ppm_file, pixel_color);
}

static t_vec3	render_pixel_color(
	t_camera *cam,
	t_world *world,
	int i,
	int j
)
{
	t_vec3			pixel_color;
	int				sample;
	t_ray			r;
	t_vec3			final_color;
	const double	pixel_samples_scale = 1.0 / cam->samples_per_pixel;

	sample = 0;
	pixel_color = (t_vec3){0, 0, 0};
	final_color = (t_vec3){0, 0, 0};
	while (sample < cam->samples_per_pixel)
	{
		r = get_ray(i, j, cam);
		pixel_color = add_vec3(pixel_color, ray_color(&r, world,
					cam->background, cam->max_depth));
		sample++;
	}
	final_color = multiply_by_scalar(pixel_color, pixel_samples_scale);
	return (final_color);
}

bool	render(t_camera *cam, t_world *world, t_rgba **colors)
{
	int		i;
	int		j;
	t_vec3	final_color;
	int		ppm_file;

	ppm_file = create_ppm_file(world, cam);
	if (ppm_file == -1)
		return (false);
	i = 0;
	while (i < cam->image_height)
	{
		j = -1;
		while (++j < cam->image_width)
		{
			final_color = render_pixel_color(cam, world, i, j);
			write_color(world, &final_color, ppm_file);
			colors[i][j].rgba = get_color(final_color.x, final_color.y,
							final_color.z, 0xFF);
		}
		i++;
		printf("Scanlines done: %5d/%d\n", i, cam->image_height);
	}
	if (world->write_to_file == true)
		close(ppm_file);
	return (true);
}
