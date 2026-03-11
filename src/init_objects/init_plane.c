/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   init_plane.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 19:01:32 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:09:00 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>

// Plane list functions
bool	plane_list_init(t_plane_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->planes = malloc(capacity * sizeof(t_plane));
	if (!list->planes)
		return (external_perror("malloc fail"), false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

void	plane_list_destroy(t_plane_list *list)
{
	if (!list)
		return ;
	if (list->planes)
		free(list->planes);
	list->planes = NULL;
	list->count = 0;
	list->capacity = 0;
}
