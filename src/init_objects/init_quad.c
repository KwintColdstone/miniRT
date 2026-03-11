/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   init_quad.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: avaliull <avaliull@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/07 18:59:25 by avaliull            #+#    #+#           */
/*   Updated: 2026/03/07 19:08:18 by avaliull            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>

// Quad list functions
bool	quad_list_init(t_quad_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->quads = malloc(capacity * sizeof(t_quad));
	if (!list->quads)
		return (external_perror("malloc fail"), false);
	list->count = 0;
	list->capacity = capacity;
	return (true);
}

void	quad_list_destroy(t_quad_list *list)
{
	if (!list)
		return ;
	if (list->quads)
		free(list->quads);
	list->quads = NULL;
	list->count = 0;
	list->capacity = 0;
}
