#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
#include "miniRT.h"

int calculate_img_height(float aspect_ratio, int image_width)
{
	int image_height;

	// Calculate the image height, and ensure that it's at least 1.
	image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
	{
		image_height = 1;
	}
	return image_height;
}

int main(int argc, char *argv[])
{
	t_camera	cam;
	t_world		world;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.image_height = calculate_img_height(cam.aspect_ratio, cam.image_width);
	cam.samples_per_pixel = 40;
	cam.max_depth = 10;
	cam.v_up = (t_vec3){0, 1, 0};
	cam.background = (t_vec3){0,0,0};

	parse(argv[1], &world, &cam);
	camera_init(&cam);
	render(&cam, &world);
	world_destroy(&world);
	return (0);
}
