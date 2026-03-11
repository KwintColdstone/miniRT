/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   init_sphere.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 18:55:58 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:07:55 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"

// Sphere list functions
bool	sphere_list_init(t_sphere_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->spheres = ft_calloc(capacity, sizeof(t_sphere));
	if (!list->spheres)
		return (external_perror("malloc fail"), false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

void	sphere_list_destroy(t_sphere_list *list)
{
	if (!list)
		return ;
	if (list->spheres)
		free(list->spheres);
	list->spheres = NULL;
	list->count = 0;
	list->capacity = 0;
}
