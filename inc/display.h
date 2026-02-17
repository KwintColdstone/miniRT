/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.h                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:09:30 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/17 17:23:50 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

#include "miniRT.h"
#include "MLX42/MLX42.h"

uint32_t	get_color(int red, int green, int blue, int opacity);

typedef union t_rgba
{
	uint32_t	rgba;
	struct
	{
		uint8_t		a;
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
	} ;
}	t_rgba;

int	display_world(
	t_camera *cam,
	t_world *world,
	mlx_t *window,
	mlx_image_t *image
);

#endif	// DISPLAY_H
