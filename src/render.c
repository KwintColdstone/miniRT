#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"

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

bool is_in_shadow(const t_world *world, const t_vec3 *point, const t_light *light)
{
	t_ray       shadow_ray;
	t_hit_record shadow_rec;
	t_interval  shadow_t;
	t_vec3      light_dir;
	double      light_distance;

	// Calculate direction and distance to light
	light_dir = subtract_vec3(light->position, *point);
	light_distance = vec3_length(light_dir);

	if (light_distance < 1e-6)
		return (false);

	light_dir = unit_vector(light_dir);

	// Move the ray origin slightly in the direction of the light
	// This prevents the ray from intersecting the same surface
	t_vec3 shadow_origin = add_vec3(*point, multiply_by_scalar(light_dir, 0.001));
	shadow_ray = (t_ray){shadow_origin, light_dir};

	// Check for occluders between point and light (but not beyond the light)
	shadow_t = (t_interval){0.001, light_distance - 0.001};

	return (world_hit(world, &shadow_ray, shadow_t, &shadow_rec));
}

t_vec3 direct_lighting(const t_world *world, t_hit_record *rec)
{
	t_vec3 direct = {0, 0, 0};
	t_vec3 ambient;
	t_vec3 light_dir;
	t_vec3 diffuse;
	double diff;

	ambient = multiply_vec3(world->ambient, rec->mat.albedo);
	direct = ambient;
	if (world->light.brightness > 0.0)
	{
		if (!is_in_shadow(world, &rec->position, &world->light))
		{
			light_dir = unit_vector(subtract_vec3(world->light.position, rec->position));
			
			// Diffuse factor (Lambert's cosine law)
			diff = fmax(dot_vec3(rec->normal, light_dir), 0.0);
	
			// Diffuse color
			diffuse = multiply_by_scalar(
				multiply_vec3(world->light.color, rec->mat.albedo),
				diff * world->light.brightness
			);
			
			direct = add_vec3(direct, diffuse);
		}
	}

	return (direct);
}

static t_vec3 ray_color(const t_ray *r, const t_world *world, t_vec3 background, int depth)
{
	t_hit_record	rec;
	t_interval	ray_t;
	t_ray		scattered;
	t_vec3		attenuation;
	t_vec3		direct;
	t_vec3		color;
	bool		did_scatter; (void) did_scatter; //unused!

	if (depth <= 0)
		return ((t_vec3){0,0,0});
	ray_t.min = 0.001;
	ray_t.max = INFINITY;
	if (!world_hit(world, r, ray_t, &rec))
	{
		return (sky(r));
		//return (background);
	}
	// Start with emitted light
	color = rec.mat.emit_color;

	// Direct lighting (ray tracing)
	direct = direct_lighting(world, &rec);
	color = add_vec3(color, direct);

	// indirect lightning (path tracing)
	if (rec.mat.type == MAT_LAMBERTIAN)
	{
		if (lambertian_scatter(r, &rec, &attenuation, &scattered))
		{
			t_vec3 indirect = ray_color(&scattered, world, background, depth - 1);
			color = add_vec3(color, multiply_vec3(attenuation, indirect));
		}
	}
	else if (rec.mat.type == MAT_METAL)
	{
		if (metal_scatter(r, &rec, &attenuation, &scattered))
		{
			t_vec3 indirect = ray_color(&scattered, world, background, depth - 1);
			color = add_vec3(color, multiply_vec3(attenuation, indirect));
		}
	}
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

	pixel_color->x = rbyte;
	pixel_color->y = gbyte;
	pixel_color->z = bbyte;

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

bool render(t_camera *cam, t_world *world, mlx_image_t *image)
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

			t_rgba	pixel_color;
			pixel_color.rgba = get_color(final_color.x, final_color.y, final_color.z, 0xFF);
			mlx_put_pixel(image, j, i, pixel_color.rgba);

			j++;
		}
		i++;
	}
	close(file);
	return (true);
}
