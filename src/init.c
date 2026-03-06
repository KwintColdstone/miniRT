#include "libft.h"
#include "miniRT.h"
#include <unistd.h>

// Sphere list functions
bool sphere_list_init(t_sphere_list *list, int capacity)
{

	if (!list || capacity <= 0)
		return (false);
	list->spheres = ft_calloc(capacity, sizeof(t_sphere));
	if (!list->spheres)
		return (false);
	list->count = 0;
	list->capacity = capacity;
		return (true);
}

void sphere_list_destroy(t_sphere_list *list)
{
	if (!list)
		return ;
	if (list->spheres)
		free(list->spheres);
	list->spheres = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Quad list functions
bool quad_list_init(t_quad_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);

	list->quads = malloc(capacity * sizeof(t_quad));
	if (!list->quads)
		return (false);

	list->count = 0;
	list->capacity = capacity;
		return (true);
}

void quad_list_destroy(t_quad_list *list)
{
	if (!list)
		return;

	if (list->quads)
		free(list->quads);
	list->quads = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Cylinder list functions
bool cylinder_list_init(t_cylinder_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);

	list->cylinders = malloc(capacity * sizeof(t_cylinder));
	if (!list->cylinders)
		return (false);
	list->count = 0;
	list->capacity = capacity;
		return (true);
}

void cylinder_list_destroy(t_cylinder_list *list)
{
	if (!list)
		return;

	if (list->cylinders)
		free(list->cylinders);
	list->cylinders = NULL;
	list->count = 0;
	list->capacity = 0;
}

// Plane list functions
bool plane_list_init(t_plane_list *list, int capacity)
{
	if (!list || capacity <= 0)
		return (false);

	list->planes = malloc(capacity * sizeof(t_plane));
	if (!list->planes)
		return (false);

	list->count = 0;
	list->capacity = capacity;
	return (true);
}

void plane_list_destroy(t_plane_list *list)
{
	if (!list)
		return;

	if (list->planes)
		free(list->planes);
	list->planes = NULL;
	list->count = 0;
	list->capacity = 0;
}

bool world_init(t_world *world, t_object_counter *c)
{
	ft_memset(world, 0, sizeof(t_world));
	if (c->sphere_cap)
	{
		if (!sphere_list_init(&world->sp_list, c->sphere_cap))
			return (minirt_perror(false, "Failed to init sphere list\n"));
	}
	if (c->quad_cap)
	{
		if (!quad_list_init(&world->qu_list, c->quad_cap))
			return (minirt_perror(false, "Failed to init quad list\n"));
	}
	if (c->cylinder_cap)
	{
		if (!cylinder_list_init(&world->cy_list, c->cylinder_cap))
			return (minirt_perror(false, "Failed to init cylinder list\n"));
	}
	if (c->plane_cap)
	{
		if (!plane_list_init(&world->pl_list, c->plane_cap))
			return (minirt_perror(false, "Failed to init plane list\n"));
	}
	return (true);
}

void world_destroy(t_world *world)
{
	if (!world)
		return;
	sphere_list_destroy(&world->sp_list);
	quad_list_destroy(&world->qu_list);
	cylinder_list_destroy(&world->cy_list);
	plane_list_destroy(&world->pl_list);
}
