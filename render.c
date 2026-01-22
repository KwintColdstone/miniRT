#include "miniRT.h"

static t_vec3 ray_color(const t_ray *r, const t_world *world, int depth)
{
	t_hit_record	rec;
	t_interval	ray_t;
	t_vec3		direction;
	t_ray		random;

	ray_t.min = 0;
	ray_t.max = INFINITY;
	if (world_hit(world, r, ray_t, &rec))
	{
		direction = random_on_hemisphere(&rec.normal);
		random = (t_ray){rec.position, direction};	
		return (multiply_by_scalar(ray_color(&random, world, depth - 1), 0.5));
	}
	//A unit vector is a vector with length/magnitude of exactly 1
	//we use it in formulas where you only need the direction not how far in
	//a particular direction it goes
	t_vec3 unit_direction = unit_vector(r->direction);
	// unit_direction.y goes from -1 to 1
	// a transforms that to a range of 0 to 1
	// so when a = 0 we get white and when a = 1 we get blue
	double a = 0.5*(unit_direction.y + 1.0);
	t_vec3 white = {1.0, 1.0, 1.0};
	t_vec3 blue = {0.5, 0.7, 1.0};
	t_vec3 w_amount = multiply_by_scalar(white,(1.0-a));
	t_vec3 b_amount = multiply_by_scalar(blue,a);
	return (add_vec3(w_amount, b_amount));
}

static void	write_color(int file, t_vec3 *pixel_color)
{
	double r = pixel_color->x; 
	double g = pixel_color->y; 
	double b = pixel_color->z;
	int rbyte = (int)(255.999 * r);
	int gbyte = (int)(255.999 * g);
	int bbyte = (int)(255.999 * b);
	char pixel[16];
	int len = sprintf(pixel, "%d %d %d\n", rbyte, gbyte, bbyte);
	write(file, pixel, len);
}

bool render(t_camera *cam, t_world *world, int image_width, int image_height)
{
	int file;
	int i;
	int j;
	int max_depth;

	max_depth = 10;
	//open file to write image to
	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1) {
		write(2, "Error opening file\n", 19);
		return (false);
	}
	//standard ppm start info
	write(file, "P3\n", 3);
	char *width = ft_itoa(image_width);
	write(file, width, ft_strlen(width));
	write(file, " ", 1);
	char *height = ft_itoa(image_height);
	write(file, height, ft_strlen(height));
	write(file, "\n", 1);
	write(file, "255\n", 4);

	//image loop
	i = 0;
	while (i < image_height)
	{
		j = 0;
		while (j < image_width)
		{
			t_vec3 pixel_column = multiply_by_scalar(cam->pixel_delta_u, (double)j);
			t_vec3 pixel_row = multiply_by_scalar(cam->pixel_delta_v, (double)i);
			t_vec3 cur_pixel = add_vec3(pixel_row, pixel_column);
			t_vec3 cur_pixel_center = add_vec3(cam->pixel00_loc, cur_pixel);

			t_vec3 ray_direction = subtract_vec3(cur_pixel_center, cam->camera_center);
			t_ray r = {cam->camera_center, ray_direction};

			t_vec3 pixel_color = ray_color(&r, world, max_depth);
			write_color(file, &pixel_color);
			j++;
		}
		i++;
	}
	close(file);
	return (true);
}
