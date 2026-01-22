#include "miniRT.h"

bool sphere_list_init(t_sphere_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);
	list->centers = malloc(capacity * sizeof(t_vec3));
	list->radii = malloc(capacity * sizeof(double));
	if (!list->centers || !list->radii) {
		free(list->centers);
		free(list->radii);
		return (false);
	}
	list->count = 0;
	list->capacity = capacity;
	return (list);
}

bool sphere_list_add(t_sphere_list *list, t_vec3 center, double radius)
{
	if (!list || list->count >= list->capacity)
		return (false);
	list->centers[list->count] = center;
	list->radii[list->count] = radius;
	list->count += 1;
	return (true);
}

void	sphere_list_destroy(t_sphere_list *list)
{
	if (!list)
		return ;
	free(list->centers);
	free(list->radii);
	list->centers = NULL;
	list->radii = NULL;
}

bool	world_init(t_world *world)
{
	if (!world)
	{
		return (false);
	}
	ft_memset(world, 0, sizeof(t_world));
	if (!sphere_list_init(&world->spheres, 10))
	{
		return (false);
	}
	sphere_list_add(&world->spheres, (t_vec3){0, 0, -1}, 0.5);
	sphere_list_add(&world->spheres, (t_vec3){0,-100.5,-1}, 100);
	return (true);
}

void world_destroy(t_world *world)
{
	if (!world) return;
	sphere_list_destroy(&world->spheres);
}
