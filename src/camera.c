#include "miniRT.h"
#include <math.h>

bool	camera_init(t_camera *cam)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame
	w = unit_vector(multiply_by_scalar(cam->orientation, -1.0));
	u = unit_vector(cross_vec3(cam->v_up, w));
	v = cross_vec3(w, u);

	// Determine viewport dimensions.
	cam->focal_length = 1.0;
	double	theta = degrees_to_radians(cam->hfov);
	double	h = tan(theta / 2);
	cam->viewport_width = 2.0 * h * cam->focal_length;
	cam->viewport_height = cam->viewport_width / cam->aspect_ratio;

	// Calculate the vectors across the horizontal and down the vertical viewport edges
	t_vec3 viewport_u = multiply_by_scalar(u, cam->viewport_width);
	t_vec3 viewport_v = multiply_by_scalar(v, -cam->viewport_height);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	cam->pixel_delta_u = divide_by_scalar(viewport_u, (double)cam->image_width);
	cam->pixel_delta_v = divide_by_scalar(viewport_v, (double)cam->image_height);

	// Calculate the location of the upper left pixel
	t_vec3 viewport_center = subtract_vec3(cam->camera_center, multiply_by_scalar(w, cam->focal_length));
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
