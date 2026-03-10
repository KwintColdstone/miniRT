#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"

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

//static bool	create_ppm_file()
//{
//	//open file to write image to
//	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (file == -1) {
//		write(2, "Error opening file\n", 19);
//		return (false);
//	}
//	standard ppm start info
//	write(file, "P3\n", 3);
//	char *width = ft_itoa(cam->image_width);
//	write(file, width, ft_strlen(width));
//	write(file, " ", 1);
//	char *height = ft_itoa(cam->image_height);
//	write(file, height, ft_strlen(height));
//	write(file, "\n", 1);
//	write(file, "255\n", 4);
//}

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
	pixel_color = (t_vec3){0,0,0};
	while (sample < cam->samples_per_pixel)
	{
		r = get_ray(i, j, cam);
		pixel_color = add_vec3(pixel_color, ray_color(&r, world, cam->background, cam->max_depth));
		sample++;
	}
	final_color = multiply_by_scalar(pixel_color, pixel_samples_scale);
	write_color(&final_color);
	return (final_color);
}

bool render(t_camera *cam, t_world *world, t_rgba **colors)
{// separate writing to ppm and regular display?
	int		i;
	int 	j;
	t_vec3	final_color;

	//if (WRITE_TO_FILE == true)
	//	create_ppm_file();
	
	//image loop

	i = 0;
	while (i < cam->image_height)
	{
		printf("\rScanlines remaining: %5d/%d\n", cam->image_height - i,
				cam->image_height); // can optimize this lol
		j = 0;
		while (j < cam->image_width)
		{
			final_color = render_pixel_color(cam, world, i, j);
			colors[i][j].rgba = get_color(final_color.x, final_color.y,
								final_color.z, 0xFF);
			j++;
		}
		i++;
	}
	//close(file);
	return (true);
}
