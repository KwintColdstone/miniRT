#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
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
	(void) argc; //unused, fix

	t_camera	cam;
	t_world		world;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.image_height = calculate_img_height(cam.aspect_ratio, cam.image_width);
	cam.samples_per_pixel = 40;
	cam.max_depth = 10;
	cam.v_up = (t_vec3){0, 1, 0};
	cam.background = (t_vec3){0,0,0};

	if (!parse(argv[1], &world, &cam))
	{
		return (1);
	}
	printf("Parsed objects:\n");
	printf("Spheres: %d, center(%f,%f,%f), radius: %f \n", world.sp_list.count, world.sp_list.spheres[0].center.x,world.sp_list.spheres[0].center.y,
	world.sp_list.spheres[0].center.z, world.sp_list.spheres[0].radius);
	printf("Planes: %d\n", world.pl_list.count);
	printf("Cylinders: %d\n", world.cy_list.count);
	printf("Quads: %d\n", world.qu_list.count);
	printf("Camera: center(%f,%f,%f) orient(%f,%f,%f) fov:%d\n",
	cam.camera_center.x, cam.camera_center.y, cam.camera_center.z,
	cam.orientation.x, cam.orientation.y, cam.orientation.z,
	cam.hfov);

	if (!camera_init(&cam))
	{
		ft_putstr_fd("failed to init camera\n", STDERR_FILENO);
		return (2);
	}
	if (!render(&cam, &world))
	{
		ft_putstr_fd("failed to render\n", STDERR_FILENO);
		return (3);
	}
	world_destroy(&world);
	return (0);
}
