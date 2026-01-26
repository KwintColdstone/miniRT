#include "miniRT.h"
#include <unistd.h>

t_vec3 sky(const t_ray *r)
{
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

static t_vec3 ray_color(const t_ray *r, const t_world *world, t_vec3 background, int depth)
{
	t_hit_record	rec;
	t_interval	ray_t;
	t_ray		scattered;
	t_vec3		attenuation;
	bool		did_scatter;

	if (depth <= 0)
		return ((t_vec3){0,0,0});
	ray_t.min = 0.001;
	ray_t.max = INFINITY;
	if (!world_hit(world, r, ray_t, &rec))
	{
		return (background);
	}
/*
	if (rec.mat.type == MAT_LAMBERTIAN)
	{
		lambertian_scatter(r, &rec, &attenuation, &scattered);
		return (multiply_vec3(attenuation, ray_color(&scattered, world, background, depth - 1)));
	}
	if (rec.mat.type == MAT_METAL)
	{
		if (metal_scatter(r, &rec, &attenuation, &scattered))
		{
			return (multiply_vec3(attenuation, ray_color(&scattered, world, background, depth - 1)));
		}
	}
*/
	// Start with emitted light
	t_vec3 color = rec.mat.emit_color;
	did_scatter = false;
	if (rec.mat.type == MAT_LAMBERTIAN)
		did_scatter = lambertian_scatter(r, &rec, &attenuation, &scattered);
	else if (rec.mat.type == MAT_METAL)
		did_scatter = metal_scatter(r, &rec, &attenuation, &scattered);
	if (did_scatter)
		color = add_vec3(color, multiply_vec3(attenuation,
						ray_color(&scattered, world, background, depth - 1)));
	return (color);

}

static double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return sqrt(linear_component);
	return 0;
}

static void	write_color(int file, t_vec3 *pixel_color)
{
	t_interval	intensity;

	double r = pixel_color->x; 
	double g = pixel_color->y; 
	double b = pixel_color->z;
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);
	intensity = (t_interval){0.000, 0.999};
	int rbyte = (int)(256 * clamp_interval(r, intensity));
	int gbyte = (int)(256 * clamp_interval(g, intensity));
	int bbyte = (int)(256 * clamp_interval(b, intensity));
	char pixel[16];
	int len = sprintf(pixel, "%d %d %d\n", rbyte, gbyte, bbyte);
	write(file, pixel, len);
}

static t_vec3	sample_square(void)
{
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	t_vec3	sample;

	sample = (t_vec3){random_double() - 0.5, random_double() - 0.5, 0};
	return (sample);
}

t_ray	get_ray(int i, int j, t_camera *cam)
{
	// Construct a camera ray originating from the origin and directed at randomly sampled
	// point around the pixel location i, j.
	t_vec3	offset;

	offset = sample_square();
	t_vec3 pixel_column = multiply_by_scalar(cam->pixel_delta_u, ((double)j + offset.x));
	t_vec3 pixel_row = multiply_by_scalar(cam->pixel_delta_v, ((double)i + offset.y));
	t_vec3 cur_pixel = add_vec3(pixel_row, pixel_column);
	t_vec3 cur_pixel_sample = add_vec3(cam->pixel00_loc, cur_pixel);

	t_vec3 ray_direction = subtract_vec3(cur_pixel_sample, cam->camera_center);
	t_ray ray = {cam->camera_center, ray_direction};
	return (ray);
}

bool render(t_camera *cam, t_world *world)
{
	t_ray	r;
	t_vec3	pixel_color;
	int file;
	int i;
	int j;
	int sample;
	double	pixel_samples_scale;

	pixel_samples_scale = 1.0 / cam->samples_per_pixel;
	//open file to write image to
	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1) {
		write(2, "Error opening file\n", 19);
		return (false);
	}
	//standard ppm start info
	write(file, "P3\n", 3);
	char *width = ft_itoa(cam->image_width);
	write(file, width, ft_strlen(width));
	write(file, " ", 1);
	char *height = ft_itoa(cam->image_height);
	write(file, height, ft_strlen(height));
	write(file, "\n", 1);
	write(file, "255\n", 4);
	
	//image loop
	i = 0;
	while (i < cam->image_height)
	{
		fprintf(stderr,"\rScanlines remaining: %d", cam->image_height - i);
		fflush(stderr);
		j = 0;
		while (j < cam->image_width)
		{
			sample = 0;
			pixel_color = (t_vec3){0,0,0};
			while (sample < cam->samples_per_pixel)
			{
				r = get_ray(i, j, cam);
				pixel_color = add_vec3(pixel_color, ray_color(&r, world, cam->background, cam->max_depth));
				sample++;
			}
			t_vec3 final_color = multiply_by_scalar(pixel_color, pixel_samples_scale);
			write_color(file, &final_color);
			j++;
		}
		i++;
	}
	close(file);
	return (true);
}
