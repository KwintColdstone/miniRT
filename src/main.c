#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "miniRT.h"
#include "display.h"

int	minirt_perror(int return_code, char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return(return_code);
}

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

void	set_camera_defaults(t_camera *cam)
{
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 400;
	cam->image_height = calculate_img_height(cam->aspect_ratio,
							cam->image_width);
	cam->samples_per_pixel = 40;
	cam->max_depth = 10;
	cam->v_up = (t_vec3){0, 1, 0};
	cam->background = (t_vec3){0,0,0};
}

void	print_parsed_objects(
	t_camera	*cam,
	t_world		*world
)
{
	printf("Parsed objects:\n");
	printf("Spheres: %d, center(%f,%f,%f), radius: %f \n",
		world->sp_list.count, world->sp_list.spheres[0].center.x,
		world->sp_list.spheres[0].center.y, world->sp_list.spheres[0].center.z,
		world->sp_list.spheres[0].radius);
	printf("Planes: %d\n", world->pl_list.count);
	printf("Cylinders: %d\n", world->cy_list.count);
	printf("Quads: %d\n", world->qu_list.count);
	printf("Camera: center(%f,%f,%f) orient(%f,%f,%f) fov:%d\n",
		cam->camera_center.x, cam->camera_center.y, cam->camera_center.z,
		cam->orientation.x, cam->orientation.y, cam->orientation.z,
		cam->hfov);
}

int main(int argc, char *argv[])
{
	t_camera	cam;
	t_world		world;
	t_exit_data	exit_data;

	exit_data.exit_code = 0;
	if (argc != 2 || !parse(argv[1], &world, &cam)) // check parsing allocations
		return (1);
	set_camera_defaults(&cam);
	if (!camera_init(&cam))
		return (minirt_perror(1, "failed to init camera\n"));
	print_parsed_objects(&cam, &world);
	exit_data.world = &world;
	exit_data.window = NULL;
	exit_data.colors = NULL;
	exit_data.exit_code = raytrace(&cam, &world);
	window_close((void *) &exit_data);
	return (1); // should not be reachable lol
}
