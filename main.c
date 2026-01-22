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

int main(void)
{
	int image_width;
	int image_height;
	float aspect_ratio;

	//image
	aspect_ratio = 16.0 / 9.0;
	image_width = 1280;
	image_height = calculate_img_height(aspect_ratio, image_width);

	//camera
	t_camera	cam;
	camera_init(&cam, image_width, image_height);

	//world
	t_world world;
	if (!world_init(&world))
	{
		ft_putstr_fd("Error: failed to init world\n", 2);
		return (1);
	}
	render(&cam, &world, image_width, image_height);
	world_destroy(&world);
	return (0);
}
