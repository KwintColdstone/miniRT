/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:06:13 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/17 17:23:42 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "miniRT.h"

uint32_t	get_color(int red, int green, int blue, int opacity)
{
	return ((red << 24) + (green << 16) + (blue << 8) + opacity);
}

int	display_world(
	t_camera *cam,
	t_world *world,
	mlx_t *window,
	mlx_image_t *image
)
{
	(void) world;
	(void) cam;
	if (mlx_image_to_window(window, image, 0, 0) < 0)
	{
		printf("PLACEHOLDER ERROR\n");
		printf("could not put image to window\n");
		return (1);
	}
	mlx_loop(window);
	mlx_terminate(window);
	return (0);
}
