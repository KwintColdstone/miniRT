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
	//camera
	t_camera	cam;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.image_height = calculate_img_height(cam.aspect_ratio, cam.image_width);
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	/*
	cam.hfov = 80;
	//cam.look_from = (t_vec3){-1,1,1};
	//cam.look_at = (t_vec3){0,0,-1};
	cam.look_from = (t_vec3){0,0,12};
	cam.look_at = (t_vec3){0,0,0};
	cam.v_up = (t_vec3){0,1,0};
	*/
	cam.hfov = 60;  // Field of view
	
	// Camera position for looking into the box
	cam.look_from = (t_vec3){2.78, 2.78, -8.0};  // Scaled: (278, 278, -800)/100
	cam.look_at = (t_vec3){2.78, 2.78, 0};       // Scaled: (278, 278, 0)/100
	cam.v_up = (t_vec3){0, 1, 0};

	cam.background = (t_vec3){0,0,0};
	camera_init(&cam);

	//world
	t_world world;
	if (!world_init(&world))
	{
		ft_putstr_fd("Error: failed to init world\n", 2);
		return (1);
	}
	render(&cam, &world);
	world_destroy(&world);
	return (0);
}
