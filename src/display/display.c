/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   display.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/02/17 16:06:13 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/06 20:12:41 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "miniRT.h"
#include "display.h"

void	window_close(void *param)
{
	t_exit_data *const	exit_data = param;
	int					i;

	if (exit_data->window)
		mlx_terminate(exit_data->window);
	if (exit_data->world)
		world_destroy(exit_data->world);
	if (exit_data->colors)
	{
		i = -1;
		while (exit_data->colors[++i])
			free(exit_data->colors[i]);
		free(exit_data->colors);
	}
	exit_data->window = NULL;
	exit_data->world = NULL;
	exit_data->colors = NULL;
	dprintf(STDERR_FILENO, "\nDEBUG: exit hook caled\n");
	exit (exit_data->exit_code);
}

static int	display_world(
	mlx_t *window,
	mlx_image_t *image
)
{
	if (mlx_image_to_window(window, image, 0, 0) < 0)
		return (external_perror("MLX - failed to put image to window\n"), 1);
	mlx_loop(window);
	return (0);
}

static t_rgba	**init_colors(t_camera *cam)
{
	t_rgba	**colors;
	int		i;

	colors = ft_calloc(cam->image_height + 1, sizeof(t_rgba *));
	if (!colors)
		return (external_perror("Failed to init colors"), NULL);
	i = -1;
	while (++i < cam->image_height)
	{
		colors[i] = ft_calloc(cam->image_width + 1, sizeof(t_rgba));
		if (!colors[i])
		{
			while (--i >= 0)
				free(colors[i]);
			free(colors);
			return (external_perror("Failed to init colors"), NULL);
		}
	}
	return (colors);
}

static void	draw_image(
	t_camera *cam,
	mlx_image_t *image,
	t_rgba **colors
)
{
	int	i;
	int	j;

	i = 0;
	while (i < cam->image_height)
	{
		j = 0;
		while (j < cam->image_width)
		{
			mlx_put_pixel(image, j, i, colors[i][j].rgba);
			j++;
		}
		i++;
	}
}

int	raytrace(
	t_camera *cam,
	t_world *world,
	t_exit_data *exit_data
)
{
	mlx_image_t	*image;
	mlx_t		*window;
	t_rgba		**colors;

	colors = init_colors(cam);
	if (colors == NULL)
		return (1);
	exit_data->colors = colors;
	if (!render(cam, world, colors))
		return (minirt_perror("Failed to render image"), 1); // check return logic
	mlx_set_setting(MLX_STRETCH_IMAGE, 1); // this does not preserve the proportions :(
	window = mlx_init(cam->image_width, cam->image_height, "miniRT", true);
	if (!window)
		return (minirt_perror("Failed to initialize window\n"), 1);
	exit_data->window = window;
	mlx_close_hook(window, window_close, (void *) exit_data);
	mlx_key_hook(window, minirt_key_hook, (void *) exit_data);
	image = mlx_new_image(window, cam->image_width, cam->image_height);
	if (!image)
		return (minirt_perror("Failed to initialize image\n"), 1);
	draw_image(cam, image, colors);
	return (display_world(window, image));
}
