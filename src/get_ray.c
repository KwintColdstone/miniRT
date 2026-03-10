/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   get_ray.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 18:41:02 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 18:50:48 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
static t_vec3	sample_square(void)
{
	t_vec3	sample;

	sample = (t_vec3){random_double() - 0.5, random_double() - 0.5, 0};
	return (sample);
}

static t_vec3	get_cur_pixel_sample(int i, int j, t_camera *cam,
				const t_vec3 offset)
{
	const t_vec3	pixel_column = multiply_by_scalar(cam->pixel_delta_u,
			((double)j + offset.x));
	const t_vec3	pixel_row = multiply_by_scalar(cam->pixel_delta_v,
			((double)i + offset.y));
	const t_vec3	cur_pixel = add_vec3(pixel_row, pixel_column);

	return (add_vec3(cam->pixel00_loc, cur_pixel));
}

// Construct a camera ray originating from the origin
// and directed at randomly sampled
// point around the pixel location i, j.
t_ray	get_ray(int i, int j, t_camera *cam)
{
	const t_vec3	offset = sample_square();
	const t_vec3	cur_pixel_sample = get_cur_pixel_sample(i, j, cam, offset);
	const t_vec3	ray_direction = subtract_vec3(cur_pixel_sample,
			cam->camera_center);

	return ((t_ray){cam->camera_center, ray_direction});
}
