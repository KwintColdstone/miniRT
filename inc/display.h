/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.h                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:09:30 by avaliull            #+#    #+#           */
/*   Updated: 2026/02/26 18:16:59 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

#include "miniRT.h"
#include "MLX42/MLX42.h"

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

typedef struct	s_exit_data {
	t_world		*world;
	mlx_t		*window;
	t_rgba		**colors;
	int			exit_code;
}	t_exit_data;

uint32_t	get_color(int red, int green, int blue, int opacity);

int	raytrace(
	t_camera *cam,
	t_world *world
);
int	display_world(
	mlx_t *window,
	mlx_image_t *image
);
// render.c
bool render(t_camera *cam, t_world *world, t_rgba **colors);

void	window_close(void* param);

#endif	// DISPLAY_H
