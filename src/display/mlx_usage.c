/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   mlx_helpers.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/06 17:35:25 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/06 17:37:50 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42.h"
#include "display.h"

void	minirt_key_hook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		window_close(param);
}

uint32_t	get_color(int red, int green, int blue, int opacity)
{
	return ((red << 24) + (green << 16) + (blue << 8) + opacity);
}
