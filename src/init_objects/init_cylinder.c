/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   init_cylinder.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 19:00:42 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:08:32 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>

// Cylinder list functions
bool	cylinder_list_init(t_cylinder_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->cylinders = malloc(capacity * sizeof(t_cylinder));
	if (!list->cylinders)
		return (external_perror("malloc fail"), false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

void	cylinder_list_destroy(t_cylinder_list *list)
{
	if (!list)
		return ;
	if (list->cylinders)
		free(list->cylinders);
	list->cylinders = NULL;
	list->count = 0;
	list->capacity = 0;
}
