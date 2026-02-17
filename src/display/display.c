/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:06:13 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/17 16:59:14 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "miniRT.h"

int	display_world(
	t_camera *cam,
	t_world *world
)
{
	(void) world;
	mlx_t	*mlx;

	mlx = mlx_init(cam->image_width, cam->image_height, "miniRT", true);
	return (0);
}
