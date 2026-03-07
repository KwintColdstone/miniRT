/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   error_and_exit.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 15:44:30 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 15:56:10 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <unistd.h>
#include <display.h>

// Function to report an error related to minirt-specific functions
void	minirt_perror(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("Description: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

// Function to report an error related to library functions that set errno
void	external_perror(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("Description: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

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
