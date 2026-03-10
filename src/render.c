#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"

//A unit vector is a vector with length/magnitude of exactly 1
//we use it in formulas where you only need the direction not how far in
//a particular direction it goes
// unit_direction.y goes from -1 to 1
// a transforms that to a range of 0 to 1
// so when a = 0 we get white and when a = 1 we get blue
static t_vec3	construct_sky_vec3(const double a) // check that name makes sense
{
	const t_vec3	white = {1.0, 1.0, 1.0};
	const t_vec3	blue = {0.5, 0.7, 1.0};
	const t_vec3	w_amount = multiply_by_scalar(white,(1.0-a));
	const t_vec3	b_amount = multiply_by_scalar(blue,a);

	return (add_vec3(w_amount, b_amount));
}

t_vec3 sky(const t_ray *r)
{
	const t_vec3	unit_direction = unit_vector(r->direction);
	const double	a = 0.5*(unit_direction.y + 1.0);

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

static t_vec3 ray_color(
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
		return ((t_vec3){0,0,0});
	color = get_direct_color(r, world, &rec);
	if (INDIRECT_LIGHTING == true)
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

static double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

static void	write_color(t_vec3 *pixel_color)
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
	// if (WRITE_TO_FILE == true)
	//char pixel[16];
	//int len = sprintf(pixel, "%d %d %d\n", rbyte, gbyte, bbyte);
	//write(file, pixel, len);
}

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
static t_vec3	sample_square(void)
{
	t_vec3	sample;

	sample = (t_vec3){random_double() - 0.5, random_double() - 0.5, 0};
	return (sample);
}

// Construct a camera ray originating from the origin and directed at randomly sampled
// point around the pixel location i, j.
t_ray	get_ray(int i, int j, t_camera *cam)
{
	t_vec3	offset;

	offset = sample_square();
	t_vec3	pixel_column = multiply_by_scalar(cam->pixel_delta_u, ((double)j + offset.x));
	t_vec3	pixel_row = multiply_by_scalar(cam->pixel_delta_v, ((double)i + offset.y));
	t_vec3	cur_pixel = add_vec3(pixel_row, pixel_column);
	t_vec3	cur_pixel_sample = add_vec3(cam->pixel00_loc, cur_pixel);
	t_vec3	ray_direction = subtract_vec3(cur_pixel_sample, cam->camera_center);
	t_ray	ray = {cam->camera_center, ray_direction};
	return (ray);
}

bool render(t_camera *cam, t_world *world, t_rgba **colors)
{// separate writing to ppm and regular display?
	t_ray	r;
	t_vec3	pixel_color;
	int i;
	int j;
	int sample;
	double	pixel_samples_scale;

	pixel_samples_scale = 1.0 / cam->samples_per_pixel;
	//open file to write image to
	//file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//if (file == -1) {
	//	write(2, "Error opening file\n", 19);
	//	return (false);
	//}
	//standard ppm start info
	//write(file, "P3\n", 3);
	//char *width = ft_itoa(cam->image_width);
	//write(file, width, ft_strlen(width));
	//write(file, " ", 1);
	//char *height = ft_itoa(cam->image_height);
	//write(file, height, ft_strlen(height));
	//write(file, "\n", 1);
	//write(file, "255\n", 4);
	
	//image loop

	i = 0;
	while (i < cam->image_height)
	{
		fprintf(stderr,"\rScanlines remaining: %d", cam->image_height - i); // not allowed !
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
			write_color(&final_color);
			colors[i][j].rgba = get_color(final_color.x, final_color.y, final_color.z, 0xFF);
			j++;
		}
		i++;
	}
	//close(file);
	return (true);
}
