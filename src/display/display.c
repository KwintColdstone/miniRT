/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:06:13 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 18:17:13 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "miniRT.h"
#include "display.h"

uint32_t	get_color(int red, int green, int blue, int opacity)
{
	return ((red << 24) + (green << 16) + (blue << 8) + opacity);
}

void	window_close(void* param)
{
	t_exit_data	*const exit_data = param;

	if (!exit_data)
	{
		dprintf(STDERR_FILENO, "\nDEBUG: no exit_data (should never happen i hope)\n");
		exit (1);
	}
	if (exit_data->window)
		mlx_terminate(exit_data->window);
	if (exit_data->world)
		world_destroy(exit_data->world);
	dprintf(STDERR_FILENO, "\nDEBUG: exit hook caled\n");
	exit (exit_data->exit_code);
}

static void	minirt_key_hook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		window_close(param);
}

int	display_world(
	mlx_t *window,
	mlx_image_t *image
)
{
	if (mlx_image_to_window(window, image, 0, 0) < 0)
		minirt_perror(1, "Failed to display image in the window\n");
	mlx_loop(window);
	mlx_terminate(window);
	return (0);
}

int	raytrace(
	t_camera *cam,
	t_world *world
)
{
	mlx_image_t	*image;
	mlx_t		*window;
	t_exit_data	exit_data;

	window = mlx_init(cam->image_width, cam->image_height, "miniRT", true);
	if (!window)
		minirt_perror(1, "Failed to initialize window\n");
	exit_data.window = window;
	mlx_close_hook(window, window_close, (void *) &exit_data);
	mlx_key_hook(window, minirt_key_hook, (void *) &exit_data);
	image = mlx_new_image(window, cam->image_width, cam->image_height);
	if (!image)
		minirt_perror(1, "Failed to initialize image\n");
	if (!render(cam, world, image))
		minirt_perror(1, "Failed to render image\n");
	return (display_world(window, image));
}
