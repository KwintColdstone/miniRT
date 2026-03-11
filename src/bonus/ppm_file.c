/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   ppm_file.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/10 19:40:12 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/10 20:37:40 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "bonus.h"

void	write_to_file(int ppm_file, t_vec3 *pixel_color)
{
	char			pixel[16];
	const int		len = sprintf(pixel, "%d %d %d\n",
			(int) pixel_color->x, (int)pixel_color->y, (int)pixel_color->z);

	write(ppm_file, pixel, len);
}

static void	write_default_ppm(
	char *width,
	char *height,
	int file
)
{
	write(file, "P3\n", 3);
	write(file, width, ft_strlen(width));
	write(file, " ", 1);
	write(file, height, ft_strlen(height));
	write(file, "\n", 1);
	write(file, "255\n", 4);
}

int	create_ppm_file(t_world *world, t_camera *cam)
{
	int		file;
	char	*width;
	char	*height;

	if (world->write_to_file == false)
		return (-2);
	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		return (external_perror("Failed to open .ppm file"), -1);
	width = ft_itoa(cam->image_width);
	if (!width)
		return (external_perror("malloc error:"), -1);
	height = ft_itoa(cam->image_height);
	if (!height)
	{
		free(width);
		return (external_perror("malloc error:"), -1);
	}
	write_default_ppm(width, height, file);
	free(height);
	free(width);
	return (file);
}
