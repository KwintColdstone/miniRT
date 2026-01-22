#include "miniRT.h"

bool	camera_init(t_camera *cam, int image_width, int image_height)
{
	//camera
	cam->focal_length = 1.0;
	cam->viewport_height = 2.0;
	cam->viewport_width = cam->viewport_height * ((double)(image_width)/image_height);
	cam->camera_center = (t_vec3){0,0,0};

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	t_vec3 viewport_u = {cam->viewport_width, 0, 0};
	t_vec3 viewport_v = {0, -(cam->viewport_height), 0};

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	cam->pixel_delta_u = divide_by_scalar(viewport_u, (double)image_width);
	cam->pixel_delta_v = divide_by_scalar(viewport_v, (double)image_height);

	// Calculate the location of the upper left pixel.
	t_vec3 fl = {0, 0, cam->focal_length};
	t_vec3 viewport_center = subtract_vec3(cam->camera_center, fl);
	t_vec3 half_u = divide_by_scalar(viewport_u, 2.0);
	t_vec3 half_v = divide_by_scalar(viewport_v, 2.0);

	// viewport_upper_left = viewport_center - half_u - half_v
	t_vec3 temp = subtract_vec3(viewport_center, half_u);
	t_vec3 viewport_upper_left = subtract_vec3(temp, half_v);

	//we now want to calculate the middle of the 0,0 pixel of the viewport
	//we are currently at the corner of the pixel we multiply both deltas by half
	//to get to the middle of the pixel
	t_vec3 pixel_deltas = add_vec3(cam->pixel_delta_u, cam->pixel_delta_v);
	t_vec3 half_pixel_offset = multiply_by_scalar(pixel_deltas, 0.5);
	cam->pixel00_loc = add_vec3(viewport_upper_left, half_pixel_offset);
	return (true);
}
