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

static void	minirt_key_hook(mlx_key_data_t keydata, void* param)
{
	t_exit_data	*const exit_data = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(exit_data->window);
		world_destroy(exit_data->world);
		exit (0);
	}
}

int	display_world(
	t_camera *cam,
	t_world *world,
	mlx_t *window,
	mlx_image_t *image
)
{
	t_exit_data	exit_data;

	exit_data.cam = cam;
	exit_data.world = world;
	exit_data.window = window;
	if (mlx_image_to_window(window, image, 0, 0) < 0)
	{
		printf("PLACEHOLDER ERROR\n");
		printf("could not put image to window\n");
		return (1);
	}
	mlx_key_hook(window, minirt_key_hook, (void *) &exit_data);
	mlx_loop(window);
	mlx_terminate(window);
	return (0);
}
