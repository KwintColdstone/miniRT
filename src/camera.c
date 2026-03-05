/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjongeri <kjongeri@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:49:33 by kjongeri          #+#    #+#             */
/*   Updated: 2026/03/05 14:51:57 by kjongeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include <math.h>

static void	calculate_viewport_dimensions(t_camera *cam)
{
	double	theta;
	double	h;

	cam->focal_length = 1.0;
	theta = degrees_to_radians(cam->hfov);
	h = tan(theta / 2);
	cam->viewport_width = 2.0 * h * cam->focal_length;
	cam->viewport_height = cam->viewport_width / cam->aspect_ratio;
}

//we now want to calculate the middle of the 0,0 pixel of the viewport
//we are currently at the corner of the pixel we multiply both deltas by half
//to get to the middle of the pixel
static void	calculate_middle_pixel00(t_camera *cam, t_vec3 viewport_upper_left)
{
	t_vec3	pixel_deltas;
	t_vec3	half_pixel_offset;

	pixel_deltas = add_vec3(cam->pixel_delta_u, cam->pixel_delta_v);
	half_pixel_offset = multiply_by_scalar(pixel_deltas, 0.5);
	cam->pixel00_loc = add_vec3(viewport_upper_left, half_pixel_offset);
}

// viewport_upper_left = viewport_center - half_u - half_v
static void	calculate_upper_left_pixel(t_camera *cam, t_vec3 viewport_u,
				t_vec3 viewport_v, t_vec3 w)
{
	t_vec3	viewport_center;
	t_vec3	half_u;
	t_vec3	half_v;
	t_vec3	temp;
	t_vec3	viewport_upper_left;

	viewport_center = subtract_vec3(cam->camera_center,
			multiply_by_scalar(w, cam->focal_length));
	half_u = divide_by_scalar(viewport_u, 2.0);
	half_v = divide_by_scalar(viewport_v, 2.0);
	temp = subtract_vec3(viewport_center, half_u);
	viewport_upper_left = subtract_vec3(temp, half_v);
	calculate_middle_pixel00(cam, viewport_upper_left);
}

bool	camera_init(t_camera *cam)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_vec3	viewport_u;
	t_vec3	viewport_v;

	w = unit_vector(multiply_by_scalar(cam->orientation, -1.0));
	u = unit_vector(cross_vec3(cam->v_up, w));
	v = cross_vec3(w, u);
	calculate_viewport_dimensions(cam);
	viewport_u = multiply_by_scalar(u, cam->viewport_width);
	viewport_v = multiply_by_scalar(v, -cam->viewport_height);
	cam->pixel_delta_u = divide_by_scalar(viewport_u, (double)cam->image_width);
	cam->pixel_delta_v = divide_by_scalar(viewport_v,
			(double)cam->image_height);
	calculate_upper_left_pixel(cam, viewport_u, viewport_v, w);
	return (true);
}
