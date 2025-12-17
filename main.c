#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
#include "miniRT.h"

double hit_sphere(const t_vec3 *center, double radius, const t_ray *r) 
{
	t_vec3 oc = subtract_vec3(*center, r->origin);
	double a = dot_vec3(r->direction, r->direction);
	double b = -2.0 * dot_vec3(r->direction, oc);
	double c = dot_vec3(oc, oc) - radius*radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant) ) / (2.0*a);
	}
}

t_vec3 ray_color(const t_ray *r) 
{
	t_vec3 red = {1.0, 0, 0};
	t_vec3 sphere_loc = {0,0,-1};
	double t = hit_sphere(&sphere_loc, 0.5, r);
	if (t > 0.0)
	{
		t_vec3 dir_hit_point = at(r, t);
		t_vec3 outward_ray = subtract_vec3(dir_hit_point, sphere_loc);
		t_vec3 normal = unit_vector(outward_ray);
		t_vec3 color = {normal.x + 1, normal.y + 1, normal.z + 1};
        return multiply_by_scalar(color, 0.5);
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

void	write_color(int file, t_vec3 *pixel_color)
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

int main(void)
{
	int i;
	int j;
	int image_height;
	int image_width;
	int file;
	float aspect_ratio;

	//open file to write image to
	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1) {
		write(2, "Error opening file\n", 19);
		return (1);
	}

	//image
	aspect_ratio = 16.0 / 9.0;
	image_width = 400;
	// Calculate the image height, and ensure that it's at least 1.
	image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
	{
		image_height = 1;
	}

	//camera
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)(image_width)/image_height);
	t_vec3 camera_center = {0,0,0};

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	t_vec3 viewport_u = {viewport_width, 0, 0};
	t_vec3 viewport_v = {0, -viewport_height, 0};

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	t_vec3 pixel_delta_u = divide_by_scalar(viewport_u, (double)image_width);
	t_vec3 pixel_delta_v = divide_by_scalar(viewport_v, (double)image_height);

	// Calculate the location of the upper left pixel.
	t_vec3 fl = {0, 0, focal_length};
	t_vec3 viewport_center = subtract_vec3(camera_center, fl);
	t_vec3 half_u = divide_by_scalar(viewport_u, 2.0);
	t_vec3 half_v = divide_by_scalar(viewport_v, 2.0);

	// viewport_upper_left = viewport_center - half_u - half_v
	t_vec3 temp = subtract_vec3(viewport_center, half_u);
	t_vec3 viewport_upper_left = subtract_vec3(temp, half_v);

	//we now want to calculate the middle of the 0,0 pixel of the viewport
	//we are currently at the corner of the pixel we multiply both deltas by half
	//to get to the middle of the pixel
	t_vec3 pixel_deltas = add_vec3(pixel_delta_u, pixel_delta_v);
	t_vec3 half_pixel_offset = multiply_by_scalar(pixel_deltas, 0.5);
	t_vec3 pixel00_loc = add_vec3(viewport_upper_left, half_pixel_offset);

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
			t_vec3 pixel_column = multiply_by_scalar(pixel_delta_u, (double)j);
			t_vec3 pixel_row = multiply_by_scalar(pixel_delta_v, (double)i);
			t_vec3 cur_pixel = add_vec3(pixel_row, pixel_column);
			t_vec3 cur_pixel_center = add_vec3(pixel00_loc, cur_pixel);

			t_vec3 ray_direction = subtract_vec3(cur_pixel_center, camera_center);
			t_ray r = {camera_center, ray_direction};

			t_vec3 pixel_color = ray_color(&r);
			write_color(file, &pixel_color);
			j++;
		}
		i++;
	}
	close(file);
	return (0);
}
